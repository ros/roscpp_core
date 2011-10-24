#!/usr/bin/env python

from setuptools import setup, find_packages

setup(name='snake',
      version='1.0',
      packages=find_packages(where='src'),
      package_dir={'': 'src'}
      )
