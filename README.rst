PFx Brick C++ API
=================

.. image:: https://img.shields.io/badge/status-in%20development-orange.svg
    :target: https://github.com/fx-bricks/pfx-brick-cpp
.. image:: https://img.shields.io/badge/license-MIT-blue.svg 
    :target: https://github.com/fx-bricks/pfx-brick-py/blob/master/LICENSE.md


This repository contains the API for developing C++ applications which communicate with the PFx Brick.

Getting Started
===============

Requirements
------------

* gcc
* hidapi
* sphinx (for documentation)

Basic Usage
===========

An example of the API can be seen below

.. code-block:: c

  #include <stdio.h>
  #include <string>
  #include "../src/pfxbrick.h"

  int main (int argc, char *argv[])
  { 
    PFxBrick brick = PFxBrick();
    if (brick.open())
    {
      brick.get_icd_rev();
      printf("ICD rev : %s\n", brick.icd_rev.c_str());
      brick.get_status();
      brick.print_status();
      brick.get_config();
      brick.print_config();
      brick.close();
    }
    return 0;
  }

-------------

Documentation
=============

* `PFx Brick Interface Control Document (ICD) v.3.36 <https://github.com/fx-bricks/pfx-brick-dev/raw/master/doc/ICD/PFxBrickICD-Rev3.36.pdf>`_ describes details of PFx Brick operation and communication protocol


If you want to learn more about PFx Brick, check out `our website <https://fxbricks.com/pfxbrick>`_.
