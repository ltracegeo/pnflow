from setuptools import setup, find_packages

setup(name='pnflow',
      version='1.0.0',
      description='Python wrapper for pnflow',
      url='',
      author='Robim',
      author_email='robim.pacheco@ltrace.com.br',
      packages=find_packages(),
      package_data={'':['*.lib']}, # This is the most important line.
      zip_safe=False)
