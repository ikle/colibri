DESCRIPTION = Colibri is a set of generic libraries
URL = https://github.com/ikle/colibri

CHILDS	= json rpc yonk conf net misc sys

include make-childs.mk

rpc.ok: json.ok
yonk.ok: json.ok misc.ok
