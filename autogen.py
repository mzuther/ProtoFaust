#!/usr/bin/python3

import pyinotify

import datetime
import os
import subprocess


class OnWriteHandler(pyinotify.ProcessEvent):
    def __init__(self, payload_command):
        print()
        self.print_current_file('initial run')

        # initialise payload command
        self.payload_command = payload_command

        # run payload once on startup
        self.run_payload()



    def print_current_file(self, filename):
        current_time = datetime.datetime.now()
        formatted_time = current_time.strftime('%H:%M:%S')

        output = '{0:s}  ==> {1:s}'.format(formatted_time, filename)
        print(output)
        print()


    # is called on completed writes
    def process_IN_CLOSE_WRITE(self, event):
        # ignore temporary files
        if event.name.endswith('#'):
            return
        # ignore compiled Python files
        elif event.name.endswith('.pyc'):
            return

        # get name of changed file
        if event.name:
            filename = os.path.join(event.path, event.name)
        else:
            filename = event.path

        # print name of changed file
        self.print_current_file(filename)

        # run payload
        self.run_payload()


    def run_payload(self):
        # run payload
        proc = subprocess.Popen(self.payload_command,
                                shell=True,
                                stdin=subprocess.PIPE,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                universal_newlines=True)

        # display output of "stdout" and "stderr" (if any)
        for pipe_output in proc.communicate():
            if pipe_output:
                print(pipe_output.strip())
                print()


# define directories to be ignored
def exclude_directories(path):
    if path.startswith('src/faust/output'):
        return True
    elif path.startswith('src/faust/main-svg'):
        return True
    else:
        return False


if __name__ == '__main__':
    # directory that should be monitored
    directory_to_watch = 'src/faust/'

    # command to be run on payload.  "unbuffer" pretends a TTY, thus
    # keeping escape sequences
    payload_command = \
      'rm -rf src/faust/main-svg/* && ' + \
      'unbuffer faust2svg --simple-names --simplify-diagrams --fold-complexity 25 src/faust/main.dsp && ' + \
      'faust -o src/faust/output/main.cpp src/faust/main.dsp'

    # create an instance of "pyinotify"
    watchmanager = pyinotify.WatchManager()

    # add a watch (will trigger on completed writes)
    watchmanager.add_watch(directory_to_watch,
                           pyinotify.IN_CLOSE_WRITE,
                           rec=True,
                           auto_add=True,
                           exclude_filter=exclude_directories)

    # create an instance of our file processor
    watchhandler = OnWriteHandler(payload_command)

    # connect to our file processor to "pyinotify"
    watchnotifier = pyinotify.Notifier(watchmanager,
                                       default_proc_fun=watchhandler)

    # keep monitoring
    watchnotifier.loop()
