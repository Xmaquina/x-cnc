import poplib

def connect_server():
    mail_server = 'pop.gmail.com'
    server_connection = poplib.POP3_SSL(mail_server)
    return server_connection

def do_login(server_connection, user_email, user_password):
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
    connection = connect_server()
    do_login(connection, user_email, user_password)
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

def main():
    text = read_mails("xmaquinaxmaquina@gmail.com", "x1maquina2")
    fn = open("teste.ngc", "w")
    for key in text:
        fn.write(text[key])
    fn.close()


if __name__ == "__main__":
    main()
