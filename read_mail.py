import poplib
import os

def connect_server():
    mail_server = 'pop.gmail.com'
    server_connection = poplib.POP3_SSL(mail_server)
    return server_connection

def do_login(server_connection, user_email, user_password):
    server_connection.user(user_email)
    server_connection.pass_(user_password)

def read_mail_body(connection_loged, mail_id):
    body = connection_loged.retr(mail_id)
    matching = [s for s in body[1] if "Message-ID" in s]
    if matching is not None:
        index = body[1].index(matching[0])
        mail_body = body[1][index+2:]
    else:
        mail_body = []
    return mail_body
	
def read_mail_subject(connection_loged, mail_id):
    body = connection_loged.retr(mail_id)
    matching = [ s for s in body[1] if "Subject" in s]
    if matching:
        return matching[0]
    return str(mail_id)

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

def get_id_from_subject(subject):
    return str(subject.replace("Subject: ", "").split("/")[0]).strip()

def get_type_from_subject(subject):
    return str(subject.replace("Subject: ", "").split("/")[1]).strip()


def save_file():
    text = read_mails("xmaquinaxmaquina@gmail.com", "x1maquina2")
    print("Len: ", len(text))
    diretorio = os.path.join("/home/gustavo/Documents/x-cnc", "arquivos")
    print("Diretorio existe:",diretorio, os.path.exists(diretorio))
    files_names = []
    i = 0
    for key in text:
        file_name = get_id_from_subject(key) + "_" + get_type_from_subject(key)  + ".ngc"
        file_name = os.path.join(diretorio, file_name)
        print("File saved:", file_name)
        fn = open(file_name, "w+")
        body = text[key]
        for b in body:
            fn.write(b+"\n")
        fn.close()
        files_names.append(file_name)

    return files_names
if __name__ == "__main__":
    main()
