import poplib

def connect_server():
    mailServer = 'pop.gmail.com'
    server_connection = poplib.POP3_SSL(mailServer)
    return server_connection

def do_login(server_connection):
    email = 'xmaquinaxmaquina@gmail.com'
    emailPass = 'x1maquina2'
    server_connection.user(email)
    server_connection.pass_(emailPass)

def read_mail_body(connection_loged, mail_id):
    mail_body = connection_loged.retr(mail_id)[1][76]
    return mail_body
	
def delete (connection_loged, mail_id):
    connection_loged.retr(mail_id)[1][13]

def check_mail_box(connection_loged):
    message_count, mailbox_size = connection_loged.stat()
    return message_count

def read_first_mail():
    connection = connect_server()
    do_login(connection)
    message_count = check_mail_box(connection)
    if(message_count != 0):
        mail_body = read_mail_body(connection, 1)
        delete(connection, 1)
        connection.quit()
    else:
        mail_body = None
    return mail_body
def read_all_mails():
    cont_mail = 0    
    while(True):
        mail = read_first_mail()
        if(mail != None):
            file_name = str(cont_mail+1) + ".gcode"
            file = open(file_name, "w")
            try:
                file.write(mail.decode())
            except AttributeError:
                file.write(mail)
            file.close()
            cont_mail = cont_mail + 1
        else:
            break
    return cont_mail


def main():
    read_emails = read_all_mails()
    print (read_emails)

if __name__ == "__main__":
    main()
