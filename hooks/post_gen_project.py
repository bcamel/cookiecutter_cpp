# This script executes after the project is generated from your cookiecutter.
# Details about hooks can be found in the cookiecutter documentation:
# https://cookiecutter.readthedocs.io/en/latest/advanced/hooks.html
#
# An example of a post-hook would be to remove parts of the project
# directory tree based on some configuration values.

import os
from cookiecutter.utils import rmtree


# Optionally remove files whose existence is tied to disabled features
def conditional_remove(condition, path):
    if condition:
        if os.path.isfile(path):
            os.remove(path)
        else:
            rmtree(path)


conditional_remove("{{ cookiecutter.license }}" == "None", "LICENSE.md")
conditional_remove("{{ cookiecutter.github_actions_ci }}" == "No", ".github")
conditional_remove(os.stat("TODO.md").st_size == 0, "TODO.md")

# Print a message about success
print("The project {{ cookiecutter.repo_name }} was successfully generated!")
print("The file FILESTRUCTURE.md describes the purpose and content of all the generated files.")
if os.path.exists("TODO.md"):
    print("A TODO list for you to finalize the generation process was also generated, see TODO.md.")
