import platform
from setuptools import setup, find_packages


if platform.system() == "Windows":
    lib_extension = "lib"
else:
    lib_extension = "so"


setup(name='pnflow',
      version='1.0.0',
      description='Python wrapper for pnflow',
      url='',
      author='Robim',
      author_email='robim.pacheco@ltrace.com.br',
      packages=find_packages(),
      package_data={'':[f'*.{lib_extension}']}, # This is the most important line.
      zip_safe=False)
