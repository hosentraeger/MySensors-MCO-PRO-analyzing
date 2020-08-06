<table border="1">
<tr><th>TC#</th><th>GW</th><th>Signing</th><th>WAIT_MS</th><th>Sketch</th><th>Results</th></tr>
<tr><td>1</td><td>Arduino</td><td>n</td><td>0</td><td>hello</td><td>working fine</td></tr>
<tr><td>2</td><td>Arduino</td><td>only GW</td><td>0</td><td>hello</td><td>GW: MCO:PRO rc=1+rc=2</td></tr>
<tr><td>3</td><td>Arduino</td><td>n</td><td>1000</td><td>hello</td><td>GW:fine, Node: MCO:PRO rc=1</td></tr>
<tr><td>4</td><td>Arduino</td><td>y</td><td>0</td><td>hello</td><td>GW: MCO:PRO rc=1 (presentation+send msg to node), Node:fine</td></tr>
<tr><td>5</td><td>Arduino</td><td>y</td><td>1000</td><td>hello</td><td>GW: MCO:PRO rc=1 (presentation+send msg to node), Node:MCO:PRO rc=1 (@presentation) (node logfile unfortunately missing)</td></tr>
<tr><td>6</td><td>Arduino</td><td>y</td><td>1000</td><td>mini</td><td>GW+Node: MCO:PRO rc=1</td></tr>
<tr><td>7</td><td>Raspberry</td><td>y</td><td>1000</td><td>mini</td><td>GW+Node: MCO:PRO rc=1</td></tr>
<tr><td>8</td><td>Raspberry</td><td>y</td><td>1000</td><td>hello</td><td>GW+Node: MCO:PRO rc=1 (presentation+send msg to node)</td></tr>
<tr><td>9</td><td>Raspberry</td><td>y</td><td>0</td><td>hello</td><td>GW: MCO:PRO rc=1, Node: according to the logs MCO:PRO, but in my memory fine, have to repeat the test</td><tr><td>10</td><td>Arduino</td><td>y</td><td>1000</td><td>mini</td><td>GW+Node: MCO:PRO rc=1</td></tr>
</table>
