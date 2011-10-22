#!/usr/bin/env python

from setuptools import setup, find_packages

setup(name='snake',
      version='1.0',
      packages=find_packages(),
      # py_modules=['snake'],
      package_dir={'': 'src'}
)
