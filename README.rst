============
vmod-hiring
============

SYNOPSIS
========

import hiring;

DESCRIPTION
===========

Hiring Varnish vmod, a vmod providing a count() function to count occurences of needle in a haystack.

FUNCTIONS
=========

count
-----

Prototype
        ::

                count(STRING haystack, STRING needle)
Return value
	INT
Description
	Returns integer value representing occurences of needle in haystack
Hiring
        ::

                set resp.http.hello = hiring.count("Example", "xa");

INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the ``varnishtest`` tool.

Building requires the Varnish header files and uses pkg-config to find
the necessary paths.

Usage::

 ./autogen.sh
 ./configure

If you have installed Varnish to a non-standard directory, call
``autogen.sh`` and ``configure`` with ``PKG_CONFIG_PATH`` pointing to
the appropriate path. For instance, when varnishd configure was called
with ``--prefix=$PREFIX``, use

::

 export PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
 export ACLOCAL_PATH=${PREFIX}/share/aclocal

The module will inherit its prefix from Varnish, unless you specify a
different ``--prefix`` when running the ``configure`` script for this
module.

Make targets:

* make - builds the vmod.
* make install - installs your vmod.
* make check - runs the unit tests in ``src/tests/*.vtc``.
* make distcheck - run check and prepare a tarball of the vmod.

If you build a dist tarball, you don't need any of the autotools or
pkg-config. You can build the module simply by running::

 ./configure
 make

Installation directories
------------------------

By default, the vmod ``configure`` script installs the built vmod in the
directory relevant to the prefix. The vmod installation directory can be
overridden by passing the ``vmoddir`` variable to ``make install``.

USAGE
=====

In your VCL you could then use this vmod along the following lines::

        import hiring;

        sub vcl_deliver {
                # This checks how many occurances of "e" is in the word "jalapeno"
                set resp.http.jalapeno = hiring.count("jalapeno", "e");
        }

COMMON PROBLEMS
===============

* configure: error: Need varnish.m4 -- see README.rst

  Check whether ``PKG_CONFIG_PATH`` and ``ACLOCAL_PATH`` were set correctly
  before calling ``autogen.sh`` and ``configure``

* Incompatibilities with different Varnish Cache versions

  Make sure you build this vmod against its correspondent Varnish Cache version.
  For instance, to build against Varnish Cache 4.1, this vmod must be built from
  branch 4.1.

START YOUR OWN VMOD
===================

The basic steps to start a new vmod from this hiring are::

  name=myvmod
  git clone libvmod-hiring libvmod-$name
  cd libvmod-$name
  ./rename-vmod-script $name

and follow the instructions output by rename-vmod-script

.. image:: https://circleci.com/gh/varnishcache/libvmod-hiring/tree/master.svg?style=svg
    :target: https://app.circleci.com/pipelines/github/varnishcache/libvmod-hiring?branch=master
