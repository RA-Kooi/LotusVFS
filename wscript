#!/usr/bin/env python3
# encoding: utf-8

top = '.'
out = 'build'

def options(opt):
    opt.load('LotusWaf', tooldir='LotusWaf')

def configure(cfg):
    cfg.load('LotusWaf', tooldir='LotusWaf')

def build(bld):
    bld.load('LotusWaf', tooldir='LotusWaf')
    bld.recurse('External')
    bld.recurse('3rdparty-build')
    #bld.project('LotusVFS')

def test(bld):
    bld.load('LotusWaf', tooldir='LotusWaf')
