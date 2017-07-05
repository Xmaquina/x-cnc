#!/usr/bin/python
import subprocess
import os
from read_mail import save_file 
import sys
import time
from daemon import Daemon

class CncDaemon(Daemon):
    def run(self):
        prog = os.path.abspath("/home/gustavo/Documents/x-cnc/x-cnc")
        output = open("/home/gustavo/Documents/x-cnc/log","w")
        while True: 
            sys.stdout.write("Start")
            file_gcode = ["/home/gustavo/Documents/x-cnc/arquivos/20_0.ngc"]
            for file_name in file_gcode:
                op = file_name.split("_")[1].split(".")[0]
                sys.stdout.write("Option to do: " + str(op) + "\n")
                sys.stdout.write("Arquivo sendo processado: " + file_name + "\n") 
                subprocess.Popen([prog,file_name,"1",op], stdout=output)
            time.sleep(100000000)

        output.close()


if __name__ == "__main__":
    daemon = CncDaemon('/tmp/cnc.pid')
    if len(sys.argv) == 2:
            if 'start' == sys.argv[1]:
                    daemon.start()
            elif 'stop' == sys.argv[1]:
                    daemon.stop()
            elif 'restart' == sys.argv[1]:
                    daemon.restart()
            else:
                    print "Unknown command"
                    sys.exit(2)
            sys.exit(0)
    else:
            print "usage: %s start|stop|restart" % sys.argv[0]
            sys.exit(2)
