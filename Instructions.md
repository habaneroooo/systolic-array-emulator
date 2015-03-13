# Introduction #



# Listing #

| { | groups operations and execute them in order (left to right) in one systolic cycle. |
|:--|:-----------------------------------------------------------------------------------|
| , | separates operations when queued with brackets |
| <x |Charge data. "x" is either "L" or "U". |
| >x |Ouput data. "x" is either "R" or "D"<br>When queued in brackets, order does not matter, it is always the last operation executed. <br>If not defined, the data on the output is the result of the last operation performed <br>
<br>
<tr><td></td><td> multiply<br></td></tr>
<tr><td>+ </td><td>add<br></td></tr>
<tr><td>- </td><td>subtract<br></td></tr>
<tr><td>/ </td><td> divide<br></td></tr>
<tr><td>ø </td><td>void  / do nothing.<br></td></tr>
<tr><td>& </td><td>logic AND<br></td></tr>
<tr><td> | </td><td> logic OR<br></td></tr></tbody></table>

Any other character is ignored. You could write fgsfds*42€lolbbq, it would end up being counted as a multiply operation only.<br>
<br>
<h1>Syntax</h1>

(t,x,y,o)	: indicates the data to process, their format and where to store the result. It is ignored for ø (= void).<br>

Ex:<br>
/(x,y) divide x by y, stores the result in o. Default stores it in the temporary register.<br>
<blockquote>"t" indicates the type of data. <br>
Data can be:<br>
"ul","sl": unsigned/signed long int<br>
"f": floating point<br>
"ud","sd": 8bit signed/unsigned int<br>
"us","ss": 16bit signed/unsigned int<br>
Default is signed long int.<br>