import smtplib
import poplib

'''read email'''

def connect_server_pop():
    mail_server = 'pop.gmail.com'
    server_connection = poplib.POP3_SSL(mail_server)
    return server_connection

def do_login_pop(server_connection, user_email, user_password):
    server_connection.user(user_email)
    server_connection.pass_(user_password)

def read_mail_body(connection_loged, mail_id):
    mail_body = str(connection_loged.retr(mail_id)[1][-1])
    return mail_body[2:-1]
	
def read_mail_subject(connection_loged, mail_id):
    mail_body = str(connection_loged.retr(mail_id)[1][-3])
    return mail_body[10:-1]

def delete (connection_loged, mail_id):
    connection_loged.retr(mail_id)[1][13]

def check_mail_box(connection_loged):
    message_count, mailbox_size = connection_loged.stat()
    return message_count

def read_mail(conection_loged, email_id):
    message_count = check_mail_box(conection_loged)
    if(message_count != 0):
        mail_body = read_mail_body(conection_loged, email_id)
        subject = read_mail_subject(conection_loged, email_id)
    else:
        mail_body = None
        subject = None
    return mail_body, subject

def read_mails(user_email, user_password):
    connection = connect_server_pop()
    do_login_pop(connection, user_email, user_password)
    cont_mail = 0
    mail_box = check_mail_box(connection)
    mails = {}
    while(mail_box):
        cont_mail = cont_mail + 1
        body_mail, subject = read_mail(connection, cont_mail)
        mails[subject] = body_mail
        mail_box = mail_box - 1
    connection.quit()
    return mails


'''send email'''


def connect_server_smtp():
    smtp_server = 'smtp.gmail.com'
    smtp_port = 587
    server_connection = smtplib.SMTP(smtp_server, smtp_port)
    return server_connection

def do_login_smtp(user_email, user_password, server_connection):
    server_connection.ehlo()
    server_connection.starttls()
    server_connection.login(user_email, user_password)

def sent_email(receiver, sender, subject, mail_body, server_loged):
    header = 'To:' + receiver + '\n' + 'From: ' + sender + '\n' + 'Subject:'+ subject + '\n'
    mail = header + mail_body
    server_loged.sendmail(sender, receiver, mail)

def sent_message(user_email, user_password, receiver, subject, mail_body):
    server = connect_server_smtp()
    do_login_smtp(user_email, user_password, server)
    sent_email(receiver, user_email, subject, mail_body, server)
    server.close()

'''cnc comunication'''

def creat_gcode_files():
    email = read_mails('xmaquinaxmaquina@gmail.com', 'x1maquina2')
    request =[]
    for key in email:
        file_name = key + ".gcode"
        file = open(file_name, "w")
        file.write(email[key])
        file.close()
        request.append(str(key))
    return request


def send_status(request, status):
    user_email = 'xmaquinaxmaquina@gmail.com'
    user_password = 'x1maquina2'
    receiver = 'xmaquinaservidor@gmail.com'
    sent_message(user_email, user_password, receiver, request, status)


def next_request(request_list):
    next_request = None
    if(request_list):
        next_request = request_list[0]
        send_status(request_list[0], 'in progress')
        del(request_list[0])
    else:
        request_list = creat_gcode_files()
        if(request_list):
            next_request = request_list[0]
            send_status(request_list[0], 'in progress')
            del(request_list[0])
        else:
            next_request = None
    return next_request, request_list
