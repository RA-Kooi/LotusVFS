# vim: ts=4 sw=4 noexpandtab

def DirectoryOfThisScript():
	import os
	return os.path.dirname(os.path.realpath(__file__)) + os.sep

def Settings( **kwargs ):
	return { 'ls': {
			'compilationDatabaseDirectory': DirectoryOfThisScript() + 'build'
		}
	}
