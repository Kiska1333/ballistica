# Released under the MIT License. See LICENSE for details.
#
# pylint: disable=missing-module-docstring, invalid-name
from __future__ import annotations

# This file is exec'ed by the spinoff system, allowing us to define
# values and behavior for this feature-set here in a programmatic way
# that can also be type-checked alongside other project Python code.

from batools.featureset import FeatureSet

# Grab the FeatureSet we should apply to.
fset = FeatureSet.get_active()

fset.requirements = {
    'core',
    'base',
    'scene_v1',
    'scene_v1_lib',
    'ui_v1',
    'ui_v1_lib',
}

# We can make use of plus stuff but can live without it.
fset.soft_requirements = {'plus'}

# We provide 'babase.app.classic'.
fset.has_python_app_subsystem = True

# If 'plus' is present, our subsystem should be inited after it
# (classic accounts key off of plus's v2 accounts)
fset.python_app_subsystem_dependencies = {'plus'}

# We want things to work without us.
fset.allow_as_soft_requirement = True
