# MySensors-MCO-PRO-analyzing
TC#	GW		Signing		WAIT_MS		Sketch	Results
1	Arduino		n		0		hello	working fine
2	Arduino		only GW		0		hello	GW: MCO:PRO rc=1+rc=2
3	Arduino		n		1000		hello	GW:fine, Node: MCO:PRO rc=1
4	Arduino		y		0					hello	GW: MCO:PRO rc=1 (presentation+send msg to node), Node:fine
5	Arduino		y		1000		hello	GW: MCO:PRO rc=1 (presentation+send msg to node), Node:MCO:PRO rc=1 (@presentation) (node logfile unfortunately missing)
6	Arduino		y		1000		mini	GW+Node: MCO:PRO rc=1
7	Raspberry	y		1000		mini	GW+Node: MCO:PRO rc=1
8	Raspberry	y		1000		hello	GW+Node: MCO:PRO rc=1 (presentation+send msg to node)
9	Raspberry	y		0		hello	GW: MCO:PRO rc=1, Node: according to the logs MCO:PRO, but in my memory fine, have to repeat the test