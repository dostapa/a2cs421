Execution Instructions<br>
<ul>
  <li>In the terminal, navigate to directory a2cs421.</li>
  <li>Run the command 'make'</li>
  <li>An executable named a2cs421 will be generated. Run it using './a2cs421'</li>
</ul>

<b>Example Run</b><br>
`
Enter Number of Variables: 8<br>
Enter Constraint Tightness: 0.33<br>
Enter Alpha: 0.8<br>
Enter r: 0.7<br>

Calculations:<br>
----------------------------<br>
Domain Size: 5<br>
Number of Constraints: 12<br>
Number of Incompatible Tuples: 8<br>
Variables: {X0,X1,X2,X3,X4,X5,X6,X7}<br>
Domain: {0,1,2,3,4}<br>

Constraints  |  Incompatible Tuples<br>
(X1, X7)     |   (0, 4)  (0, 0)  (1, 2)  (1, 4)  (2, 4)  (3, 3)  (3, 4)  (4, 4)<br>
(X1, X6)     |   (0, 2)  (0, 4)  (0, 1)  (0, 0)  (0, 3)  (3, 3)  (1, 4)  (4, 4)<br>
(X2, X7)     |   (0, 1)  (1, 4)  (0, 4)  (0, 3)  (1, 3)  (3, 3)  (3, 4)  (2, 2)<br>
(X1, X3)     |   (0, 1)  (1, 4)  (1, 1)  (0, 2)  (2, 4)  (3, 3)  (2, 2)  (1, 2)<br>
(X0, X4)     |   (0, 2)  (0, 1)  (0, 3)  (2, 3)  (0, 0)  (1, 1)  (1, 4)  (3, 3)<br>
(X2, X6)     |   (1, 2)  (0, 2)  (2, 2)  (1, 4)  (0, 4)  (3, 3)  (3, 4)  (4, 4)<br>
(X0, X1)     |   (0, 2)  (1, 3)  (0, 1)  (0, 3)  (0, 4)  (1, 2)  (3, 4)  (4, 4)<br>
(X0, X5)     |   (0, 1)  (1, 4)  (0, 0)  (2, 3)  (1, 3)  (1, 1)  (2, 4)  (4, 4)<br>
(X4, X7)     |   (0, 0)  (1, 4)  (1, 2)  (0, 2)  (2, 4)  (3, 3)  (1, 1)  (4, 4)<br>
(X3, X7)     |   (0, 3)  (1, 1)  (2, 2)  (2, 3)  (1, 4)  (0, 0)  (0, 2)  (4, 4)<br>
(X5, X7)     |   (1, 2)  (0, 2)  (2, 2)  (1, 3)  (2, 3)  (0, 3)  (2, 4)  (4, 4)<br>
(X6, X7)     |   (1, 1)  (1, 3)  (0, 4)  (2, 3)  (2, 4)  (3, 3)  (3, 4)  (0, 3)<br>
p=0.330000 < pt(0.681093) -> Generated CSP instances are guaranteed to be consistent<br>.
Solution:<br>
X0=1<br>
X1=1<br>
X2=1<br>
X3=0<br>
X4=2<br>
X5=0<br>
X6=0<br>
X7=1<br>
`

