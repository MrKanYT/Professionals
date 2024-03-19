import os
import os.path

from anytree import AnyNode, RenderTree, AsciiStyle
from anytree.importer import DictImporter, JsonImporter
from anytree.walker import Walker, WalkError
import anytree.cachedsearch


class PathNotFoundError(Exception):

    def __init__(self, name_from: str, name_to: str):
        super().__init__(f"Failed to find a path from '{name_from}' to '{name_to}'")


class Waypoint(AnyNode):
    name: str
    path_to: str
    path_from: str

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        if not hasattr(self, "path_to"):
            self.path_to = ""

        if not hasattr(self, "path_from"):
            self.path_from = ""

        if not hasattr(self, "path_from_start"):
            self.path_from_start = ""

        if not hasattr(self, "path_from_stop"):
            self.path_from_stop = ""

        if not hasattr(self, "name"):
            self.name = ""


class Navigator:

    current_waypoint: Waypoint

    _location_path: str
    _root_waypoint: Waypoint
    _walker: Walker
    _commands_separator: str

    def __init__(self, location_path: str, start: str | None = None, commands_separator: str = " "):
        self._location_path = location_path
        self._commands_separator = commands_separator

        self._root_waypoint = Navigator.read_location(self._location_path)
        self._walker = Walker()

        if start is not None:
            self.current_waypoint = self.get_waypoint(start)
            if self.current_waypoint is None:
                print(f"Unknown start location: '{start}'. Starting at the root waypoint")
                self.current_waypoint = self._root_waypoint
        else:
            self.current_waypoint = self._root_waypoint

    @staticmethod
    def read_location(path: str) -> Waypoint:
        if not os.path.isfile(path):
            raise FileNotFoundError(path)

        dict_importer = DictImporter(Waypoint)
        json_importer = JsonImporter(dict_importer)

        with open(path, "r", encoding="utf-8") as f:
            return json_importer.read(f)

    def get_waypoint(self, name: str) -> Waypoint | None:
        return anytree.cachedsearch.find_by_attr(self._root_waypoint, name)

    def set_current_waypoint(self, name: str):
        wp = self.get_waypoint(name)
        if wp is None:
            raise NameError(f"Unknown waypooint: '{name}'")
        self.current_waypoint = wp

    def find_path(self, target: Waypoint | str) -> list[str]:
        if isinstance(target, str):
            _target = self.get_waypoint(target)
            if _target is None:
                raise NameError(f"Unknown waypoint: '{target}'")
            target = _target

        try:
            upwards, common, downwards = self._walker.walk(self.current_waypoint, target)
        except WalkError:
            raise PathNotFoundError(self.current_waypoint.name, target.name)

        result = []

        def add(commands: str):
            sp = commands.strip().split(self._commands_separator)
            for c in sp:
                if c:
                    result.append(c)

        for wp in upwards:
            add(wp.path_from)

        for wp in downwards:
            add(wp.path_to)

        return result


if __name__ == "__main__":
    navigator = Navigator("locations/test_loc.json")
    print(navigator.find_path("qr_code"))
    navigator.set_current_waypoint("qr_code")
    print(navigator.find_path("wp0"))
    navigator.set_current_waypoint("wp0")
    print(navigator.find_path("spawn"))
    navigator.set_current_waypoint("spawn")