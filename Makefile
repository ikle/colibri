DESCRIPTION = Colibri is a set of generic libraries
URL = https://github.com/ikle/colibri

CHILDS	= json rpc conf net misc sys

include make-childs.mk

rpc.ok: json.ok
