import smtplib

def connect_server():
    smtp_server = 'smtp.gmail.com'
    smtp_port = 587
    server_connection = smtplib.SMTP(smtp_server, smtp_port)
    return server_connection

def do_login(user_email, user_password, server_connection):
    server_connection.ehlo()
    server_connection.starttls()
    server_connection.login(user_email, user_password)

def sent_email(receiver, sender, subject, mail_body, server_loged):
    header = 'To:' + receiver + '\n' + 'From: ' + sender + '\n' + 'Subject:'+ subject + '\n'
    mail = header + mail_body
    server_loged.sendmail(sender, receiver, mail)

def sent_message(user_email, user_password, receiver, subject, mail_body):
    server = connect_server()
    do_login(user_email, user_password, server)
    sent_email(receiver, user_email, subject, mail_body, server)
    server.close()
