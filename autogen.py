#!/usr/bin/python3

"""ProtoFaust
   ==========
   DSP prototyping in Faust for VCV Rack

   Copyright (c) 2019-2020 Martin Zuther (http://www.mzuther.de/) and
   contributors

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Thank you for using free software!

"""

import pyinotify

import datetime
import os
import subprocess


class OnWriteHandler(pyinotify.ProcessEvent):
    def __init__(self, payload_command):
        print()
        print('==> initial run')
        print()

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
        print('==> ' + filename)
        print()

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
    if path.startswith('src/faust/main-svg'):
        return True
    else:
        return False


if __name__ == '__main__':
    # directory that should be monitored
    directory_to_watch = 'src/faust/'

    # command to be run on payload.  "unbuffer" pretends a TTY, thus
    # keeping escape sequences
    payload_command = 'make faust-clean && make faust'

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
