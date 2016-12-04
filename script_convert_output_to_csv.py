import sys
import collections
import re

expressions = [(re.compile('of .* tests', re.IGNORECASE), ''), \
	(re.compile('milliseconds', re.IGNORECASE), ''), \
	(re.compile(':.*size = ', re.IGNORECASE), '_size:'), \
	(re.compile(':.*total time = ', re.IGNORECASE), '_total:'), \
	(re.compile(':.*unserialize time = ', re.IGNORECASE), '_unserialize:'),\
	(re.compile(':.*serialize time = ', re.IGNORECASE), '_serialize:')]

dic = collections.OrderedDict()
data = 0
for line in open(sys.argv[1]):
	line = line.rstrip('\n').\
		replace('>> Test incoming with a data size of ', 'nitems:').\
		replace('>> ', 'testid:').replace(' iterations','').\
		replace('performing ', 'iterations:').\
		replace(' bytes', '').replace('unserialized data has ','bytes:')
	for expr, replace_value in expressions:
		line = expr.sub(replace_value, line)
	if len(line) == 0:
		continue

	key, value = line.split(':')
	if key == 'nitems':
		data += 1
	if key not in dic:
		dic[key] = []
	dic[key] += [float(value)]

for key in dic.keys():
	sys.stdout.write(key)
	if key != list(dic.keys())[-1]:
		sys.stdout.write(';')
	else:
		sys.stdout.write('\n')

for i in range(data):
	for key in dic.keys():
		if 'serialize' in key or 'unserialize' in key or 'total' in key:
			sys.stdout.write(str((dic[key][i]/dic['iterations'][i])))
		else:
			sys.stdout.write(str(dic[key][i]))

		if key != list(dic.keys())[-1]:
			sys.stdout.write(';')
		else:
			sys.stdout.write('\n')
