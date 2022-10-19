"""
osops - OS related operations
"""

import os
import shutil
import sys

from SCons.Script import *


def prepend_env_var(env, dirnode, env_var="PATH"):
    """
    Prepend a directory to an Environment's PATH environment variable
    :param env: Environment object (Environment)
    :param dirnode: A directory node to prepend to the PATH environment variable (Dir)
    :param env_var: Environment variable (str)
    """
    env.PrependENVPath(env_var, Dir(dirnode).abspath)


def append_env_var(env, dirnode, env_var="PATH"):
    """
    Prepend a directory to an Environment's PATH environment variable
    :param env: Environment object (Environment)
    :param dirnode: A directory node to prepend to the PATH environment variable (Dir)
    :param env_var: Environment variable (str)
    """
    env.AppendENVPath(env_var, Dir(dirnode).abspath)


def is_windows():
    return "win32" == sys.platform


def is_linux():
    return sys.platform.startswith("linux")


def is_macos():
    return "darwin" == sys.platform


def get_python_exe():
    """
    :return: python executable file name, python3 if it exists in PATH else return python.

    For Windows, use python unconditionally. Windows comes installed with both stub `python3` and `python` programs that
    points to the Microsoft Store where the actual Python can be installed.
    Manual Python installations from the Python website directly come with `python` only.
    """
    ret = "python"
    if not is_windows():
        if shutil.which("python3"):
            ret = "python3"
    return ret

