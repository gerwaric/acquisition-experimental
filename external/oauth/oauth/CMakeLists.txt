# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from oauth.pro.

#####################################################################
## NetworkAuth Module:
#####################################################################

#qt_internal_add_module(NetworkAuth
#    SOURCES
target_sources(acquisition PRIVATE
        qabstractoauth.cpp qabstractoauth.h private/qabstractoauth_p.h
        qabstractoauth2.cpp qabstractoauth2.h private/qabstractoauth2_p.h
        qabstractoauthreplyhandler.cpp qabstractoauthreplyhandler.h private/qabstractoauthreplyhandler_p.h
        qoauth1.cpp qoauth1.h private/qoauth1_p.h
        qoauth1signature.cpp qoauth1signature.h private/qoauth1signature_p.h
        qoauth2authorizationcodeflow.cpp qoauth2authorizationcodeflow.h private/qoauth2authorizationcodeflow_p.h
        qoauthglobal.h
        qoauthhttpserverreplyhandler.cpp qoauthhttpserverreplyhandler.h private/qoauthhttpserverreplyhandler_p.h
        qoauthoobreplyhandler.cpp qoauthoobreplyhandler.h private/qoauthoobreplyhandler_p.h
    #[[
    LIBRARIES
        Qt::CorePrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Network
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
    NO_GENERATE_CPP_EXPORTS
    #]]
)

#[[
qt_internal_extend_target(NetworkAuth CONDITION QT_FEATURE_urischeme_replyhandler
    SOURCES
        qoauthurischemereplyhandler.cpp qoauthurischemereplyhandler.h
    LIBRARIES
        Qt::Gui
)

#### Keys ignored in scope 1:.:.:oauth.pro:<TRUE>:
# MODULE = "networkauth"
qt_internal_add_docs(NetworkAuth
    doc/qtnetworkauth.qdocconf
)
#]]
