import pathlib
import os
import inspect
from contextlib import suppress

class Template:
    _template = ""
    _filepath = ""

    def __repr__(self):
        name = self.__class__.__name__
        args = self.__init__.__code__.co_varnames
        params = ", ".join((f"{arg}={self.__dict__[arg].__repr__()}" for arg in args if arg in self.__dict__))
        return f"{name}({params})"

    def __getitem__(self, key):
        value = self.__getattribute__(key)
        if callable(value):
            return value()
        return value

    def filepath(self):
        return pathlib.Path(self._filepath.format_map(self)).resolve()

    def scriptpath(self):
        start  = os.path.realpath(self.filepath())
        target = os.path.realpath(inspect.getfile(self.__class__))
        return os.path.relpath(target,start)

    def __str__(self):
        return self._template.format_map(self).strip()
