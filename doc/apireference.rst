.. _apireference:

***********************
PFx Brick API Reference
***********************

The PFx Brick API has a top level :obj:`PFxBrick` class object.  An instance of :obj:`PFxBrick` is used to open, maintain, and close an operating session with a PFx Brick.  This class internally contains several supporting child classes used as convenient containers for related data.  In particular, it contains a :obj:`PFxConfig` and :obj:`PFxDir` class which store configuration and file system data respectively.

The :obj:`PFxAction` class is used to specify actions the PFx Brick can perform including motor control, lighting effects, and sound effects.  It has many supporting methods to conveniently specify popular actions.  A host application can also directly modify the field attributes of a :obj:`PFxAction` instance to specify a detailed action description.  Details of specifying these fields can be found in the `PFx Brick Interface Control Document (ICD) <https://www.fxbricks.com//downloads/PFxBrickICD-Rev3.36.pdf>`_.

This page summarizes the main functional groups of functionality contained in this API in sections that follow.

Connection
----------

Functions to establish a connected session with a PFx Brick.

.. hlist:: 
    :columns: 2
    
    * :cpp:func:`PFxBrick::open`
    * :cpp:func:`PFxBrick::close`
      
  
Information
-----------

Functions to get information and status from the PFx Brick.

.. hlist::
    :columns: 2

    * :cpp:func:`PFxBrick::get_icd_rev` 
    * :cpp:func:`PFxBrick::get_status`  
    * :cpp:func:`PFxBrick::print_status`
    * :cpp:func:`PFxBrick::get_name`    
    * :cpp:func:`PFxBrick::set_name`    
  
Configuration
-------------

Functions which query and modify PFx Brick configuration and settings.

.. hlist::
    :columns: 2

    * :cpp:func:`PFxBrick::get_config`
    * :cpp:func:`PFxBrick::set_config`
    * :cpp:func:`PFxBrick::print_config`
    * :cpp:func:`PFxBrick::reset_factory_config`
    
Event/Action LUT
----------------

Functions which query and modify the event/action look up table in the PFx Brick.

.. hlist::
    :columns: 2

    * :cpp:func:`PFxBrick::get_action`
    * :cpp:func:`PFxBrick::get_action_by_address`
    * :cpp:func:`PFxBrick::set_action`
    * :cpp:func:`PFxBrick::set_action_by_address`
  

