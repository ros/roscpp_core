#!/usr/bin/env python

#arg1 context.py file
#arg2 template.em (in)
#arg3 template.out

import sys, em

print "Now I would expand the .em template file", sys.argv[2]
interpreter = em.Interpreter()
out = open(sys.argv[3], 'w')

out.write( interpreter.string("@{execfile('"=sys.argv[2]="')}\n")
out.write( interpreter.file(open(sys.argv[2])) )
interpreter.shutdown()

