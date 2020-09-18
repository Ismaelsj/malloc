
import re
import subprocess as cmd
import os
import sys
import shlex

class bcolors:
    OK = '\033[92m'
    FAIL = '\033[91m'
    BOLD = '\033[94m'
    ENDC = '\033[0m'

os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))

bin_folder = "bin/"
test_folder = "tests/"
test_files = ["test0.c", "test1.c", "test2.c", "test3.c", "test3++.c", "test4.c"]
lib_inc = "../../inc"

#############################################################
# functions
def page_reclaims(prog):
    com = "./run.sh /usr/bin/time -l ./" + bin_folder + prog
    pipe = cmd.Popen(com.split(), stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    m = re.search('([0-9]+?)[ \t]+page[ \t]+reclaims', str(errput))
    if m:
        found = m.group(1)
        return int(found)
    return ""

def cmd_output(com):
    pipe = cmd.Popen(com, stdout=cmd.PIPE, stderr=cmd.PIPE)
    output, errput = pipe.communicate()
    return output, errput

def cmp_output(prog, to_compare):
    com = str("./run.sh ./" + bin_folder + prog)
    output = cmd_output(com.split())
    print("output :", output[0].decode("utf-8"))
    print("to_compare :", to_compare)
    if output[0].decode("utf-8") == to_compare:
        print(bcolors.OK + "The output is the one expected !" + bcolors.ENDC)
    else:
        print(bcolors.FAIL + "The output is not the one expected." + bcolors.ENDC)

#############################################################
# compilation
com = "rm -rf " + bin_folder
cmd.call(com.split())
com = "mkdir " + bin_folder
cmd.call(com.split())

for f in test_files:
    output_file = f[:-2]
    com = "gcc -w -o " + bin_folder + output_file + " " + test_folder + f + " -I " + lib_inc + "-w"
    cmd.call(com.split())

#############################################################
# malloc
pr0 = page_reclaims("test0")
pr1 = page_reclaims("test1")
print(bcolors.BOLD + "Test malloc" + bcolors.ENDC)
print("Number of page reclaim for test1: " + str(pr1))
print("For question1 the result is (out of 5):")
if pr1 < 255:
    print(bcolors.FAIL + "moins de 255 pages, la mémoire réservée est insuffisante: 0" + bcolors.ENDC)
elif pr1 > 1023:
    print(bcolors.OK + "1023 pages et plus, le malloc fonctionne mais consomme une page minimum à chaque allocation: 1" + bcolors.ENDC)
elif pr1 > 513 and pr1 < 1022:
    print(bcolors.OK + "entre 513 pages et 1022 pages, le malloc fonctionne mais l'overhead est trop important: 2" + bcolors.ENDC)
elif pr1 > 313 and pr1 < 512:
    print(bcolors.OK + "entre 313 pages et 512 pages, le malloc fonctionne mais l'overhead est très important: 3" + bcolors.ENDC)
elif pr1 > 273 and pr1 < 312:
    print(bcolors.OK + "entre 273 pages et 312 pages, le malloc fonctionne mais l'overhead est important: 4" + bcolors.ENDC)
elif pr1 > 255 and pr1 < 272:
    print(bcolors.OK + "entre 255 et 272 pages, le malloc fonctionne et l'overhead est raisonnable: 5" + bcolors.ENDC)

print("\n")
#############################################################
# Free
pr2 = page_reclaims("test2")
print(bcolors.BOLD + "Test free" + bcolors.ENDC)
print("Page reclaims for test0: " + str(pr0) + " Page reclaims for test2: " + str(pr2))
if pr2 - pr0 <= 3:
    print(bcolors.OK + "Max 3 page reclaim more than test0. The free is working as expected !" + bcolors.ENDC)
elif pr2 < pr1:
    print(bcolors.OK + "Free is functionning." + bcolors.ENDC)
else:
    print(bcolors.FAIL + "The free does not work." + bcolors.ENDC)

print("\n")
#############################################################
# Realloc
print(bcolors.BOLD + "Test realloc" + bcolors.ENDC)
cmp_output("test3", "Bonjours\nBonjours\n")

print("\n")
#############################################################
# Realloc ++
print(bcolors.BOLD + "Test realloc++" + bcolors.ENDC)
cmp_output("test3++", "Bonjours\nBonjours\n")

print("\n")
#############################################################
# Errors
print(bcolors.BOLD + "Test errors" + bcolors.ENDC)
cmp_output("test4", "Bonjours\n")

print("\n")
#############################################################
# show_alloc_mem
# For this test to work, you need to have the libmalloc_darwin...
# in the current directory.
print(bcolors.BOLD + "Test print_alloc_mem" + bcolors.ENDC)
com = "gcc -w -o " + bin_folder + "test5" + " " + test_folder + "test5.c" + "  -L. -lft_malloc -I " + lib_inc
cmd.call(com.split())
com = "./" + bin_folder + "test5"
output = cmd_output(com.split())
print(output[0].decode("utf-8"))