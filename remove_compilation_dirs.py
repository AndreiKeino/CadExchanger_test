# -*- coding: utf-8 -*-
"""
Created on Tue May 30 18:41:42 2023

@author: Andrei
"""

# script deletes folders which begins with 'Debug' and 'Release'

# !!! script should be placed in the root folder of the solution

from pathlib import Path
import sys
import os
import shutil


class colors:
    
    '''Colors class:reset all colors with colors.reset; two
    sub classes fg for foreground
    and bg for background; use as colors.subclass.colorname.
    i.e. colors.fg.red or colors.bg.greenalso, the generic bold, disable,
    underline, reverse, strike through,
    and invisible work with the main class i.e. colors.bold'''

    reset = '\033[0m'
    bold = '\033[01m'
    disable = '\033[02m'
    underline = '\033[04m'
    reverse = '\033[07m'
    strikethrough = '\033[09m'
    invisible = '\033[08m'
    
    
    class fg:
        black = '\033[30m'
        red = '\033[31m'
        green = '\033[32m'
        orange = '\033[33m'
        blue = '\033[34m'
        purple = '\033[35m'
        cyan = '\033[36m'
        lightgrey = '\033[37m'
        darkgrey = '\033[90m'
        lightred = '\033[91m'
        lightgreen = '\033[92m'
        yellow = '\033[93m'
        lightblue = '\033[94m'
        pink = '\033[95m'
        lightcyan = '\033[96m'
    
    
    class bg:
  		
        black = '\033[40m'
        red = '\033[41m'
        green = '\033[42m'
        orange = '\033[43m'
        blue = '\033[44m'
        purple = '\033[45m'
        cyan = '\033[46m'
        lightgrey = '\033[47m'

# print(colors.bg.green, "SKk", colors.fg.red, "Amartya")
# print(colors.bg.lightgrey, "SKk", colors.fg.red, "Amartya")
 
dir_patterns = ["Debug", "Release", "bin", "obj", '.vs', 'x64']

if __name__ == "__main__":
    
    
    script_dir = os.path.abspath( os.path.dirname(sys.argv[0]))
    print(colors.bg.black, colors.fg.green, 
          'script_dir = ', script_dir, '\n')
    
    paths_to_delete = []
    path_obj = Path(script_dir)
    
    for p in dir_patterns:
        paths_to_delete.extend(path_obj.rglob(p))
    
    print(colors.bg.black, 
          colors.fg.lightgrey, 
          'paths to delete:\n', 
          paths_to_delete)
    
    if len(paths_to_delete) == 0:
         print(colors.bg.lightgrey, colors.fg.red,
               '\nDirectory to delete list is empty, nothing to delete.')    
    
    # sys.exit()
    for p in paths_to_delete:
        pass
        print(colors.bg.black, colors.fg.green,
                    '\nremoving tree: \n ', p)
        try:
            # raise ValueError('Some exception')
            shutil.rmtree(p)
        except Exception as  e:
            err = '\nFailed to delete directory \n' + str(p)
            err += "\n" + str(e)
            print(colors.bg.black, colors.fg.red, err)
            
    print(colors.bg.black, colors.fg.green, "done...")
                    
