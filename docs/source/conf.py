# Configuration file for the Sphinx documentation builder.
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
project = 'ROS2 DiffDrive Robot'
copyright = '2026, dagebg, David Geßner'
author = 'David Geßner'
release = '0.1'

# -- General configuration ---------------------------------------------------
extensions = [
    'breathe',                  # C++ API docs via Doxygen XML
    'sphinx.ext.autodoc',       # Python docstring extraction
    'sphinx.ext.viewcode',      # adds "view source" links
    'sphinx.ext.napoleon',      # Google/NumPy style docstrings
    #'myst_parser',              # Markdown support
]

templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Breathe configuration ---------------------------------------------------
# Points to where Doxygen will output its XML (we create this later)
breathe_projects = {
    'ros2-diffdrive-robot': '../doxygen_output/xml'
}
breathe_default_project = 'ros2-diffdrive-robot'

# -- HTML output -------------------------------------------------------------
html_theme = 'furo'             
html_static_path = ['_static']

html_title = 'ROS2 DiffDrive Robot'