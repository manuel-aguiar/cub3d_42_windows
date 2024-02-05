/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_teste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:48:13 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 12:48:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm_parser.h"


char *g_teste[] = {
/* columns rows colors chars-per-pixel */
"128 128 250 2 ",
"   c #000000",
".  c #0E0E0E",
"X  c #070609",
"o  c #0D130B",
"O  c #0D0B12",
"+  c #150B17",
"@  c #1B1A1C",
"#  c #161618",
"$  c #0F1513",
"%  c #20191E",
"&  c #12230F",
"*  c #1A2718",
"=  c #1B3217",
"-  c #0F240E",
";  c #21291E",
":  c #1E1721",
">  c #221C23",
",  c #211620",
"<  c #1E2A23",
"1  c #242324",
"2  c #252B24",
"3  c #2A2C2B",
"4  c #272929",
"5  c #2B332A",
"6  c #2C3C2B",
"7  c #263525",
"8  c #313933",
"9  c #21501C",
"0  c #2B4528",
"q  c #31472E",
"w  c #335A2D",
"e  c #374A35",
"r  c #3A5E34",
"t  c #395836",
"y  c #2B562A",
"u  c #1C7A20",
"i  c #287929",
"p  c #3B6435",
"a  c #3C6B35",
"s  c #3D6539",
"d  c #3E6B3A",
"f  c #366633",
"g  c #3B7537",
"h  c #316B2C",
"j  c #207E1C",
"k  c #42573D",
"l  c #424C3E",
"z  c #426C3B",
"x  c #43653E",
"c  c #42733C",
"v  c #437C3C",
"b  c #437339",
"n  c #3E6643",
"m  c #3E4F48",
"M  c #465945",
"N  c #4D534D",
"B  c #446C42",
"V  c #4B6C45",
"C  c #4A6747",
"Z  c #52694C",
"A  c #4A7746",
"S  c #53774D",
"D  c #576A56",
"F  c #597756",
"G  c #4D6E53",
"H  c #6A7568",
"J  c #5D735F",
"K  c #188E19",
"L  c #17AB17",
"P  c #1BB41C",
"I  c #16B817",
"U  c #0DB410",
"Y  c #20B11F",
"T  c #3A8636",
"R  c #389736",
"E  c #2C8F29",
"W  c #1EB521",
"Q  c #1CAF20",
"!  c #29AB29",
"~  c #23B324",
"^  c #2CB32B",
"/  c #28B427",
"(  c #3CA939",
")  c #3AB837",
"_  c #31B42E",
"`  c #1F8320",
"'  c #45873C",
"]  c #45963D",
"[  c #42A73D",
"{  c #43BB3C",
"}  c #3AC535",
"|  c #30C52C",
" . c #41C43D",
".. c #4B8544",
"X. c #4B8C44",
"o. c #4A8747",
"O. c #538B4B",
"+. c #53864A",
"@. c #4B9344",
"#. c #4B9846",
"$. c #53934C",
"%. c #55984B",
"&. c #5B8C54",
"*. c #5A8857",
"=. c #5C9454",
"-. c #559C52",
";. c #5C9C53",
":. c #5A9658",
">. c #4F8450",
",. c #648A5B",
"<. c #63935C",
"1. c #629C5B",
"2. c #629856",
"3. c #49A546",
"4. c #54A84C",
"5. c #4ABA45",
"6. c #56BB4C",
"7. c #59A655",
"8. c #5BB953",
"9. c #65A95B",
"0. c #65BA5A",
"q. c #5D8664",
"w. c #698C63",
"e. c #688966",
"r. c #6B9465",
"t. c #659C63",
"y. c #6A9D63",
"u. c #6A9569",
"i. c #739B6D",
"p. c #72966A",
"a. c #778976",
"s. c #7B9375",
"d. c #7D9C7A",
"f. c #789875",
"g. c #719170",
"h. c #64A263",
"j. c #6BAC63",
"k. c #6CA56B",
"l. c #6CAC6B",
"z. c #68A664",
"x. c #72AB6C",
"c. c #73A56A",
"v. c #6DBB62",
"b. c #6BB364",
"n. c #74B96A",
"m. c #6FA472",
"M. c #78A876",
"N. c #7BB775",
"B. c #56C54C",
"V. c #5DC253",
"C. c #5BCA53",
"Z. c #58CF4B",
"A. c #65C759",
"S. c #63D354",
"D. c #69D759",
"F. c #6BCF59",
"G. c #6AE45A",
"H. c #6BC664",
"J. c #76C36A",
"K. c #7BCC6D",
"L. c #75C768",
"P. c #6DD662",
"I. c #75DB64",
"U. c #7BDC6C",
"Y. c #78D469",
"T. c #7DCB73",
"R. c #7BC372",
"E. c #7DD474",
"W. c #78E668",
"Q. c #76ED6A",
"!. c #82987D",
"~. c #818E79",
"^. c #82A67B",
"/. c #83B97B",
"(. c #84CD7B",
"). c #85C87A",
"_. c #84D375",
"`. c #83DB74",
"'. c #84D47A",
"]. c #89D77B",
"[. c #81D56E",
"{. c #88E678",
"}. c #89EE75",
"|. c #8A7F85",
" X c #7C9484",
".X c #878B86",
"XX c #899886",
"oX c #979995",
"OX c #91958F",
"+X c #8AA886",
"@X c #88B786",
"#X c #93B58C",
"$X c #9AA395",
"%X c #99B796",
"&X c #92A58C",
"*X c #A59BA4",
"=X c #ABB7A9",
"-X c #9CBCA3",
";X c #8BC984",
":X c #94C98A",
">X c #8BD683",
",X c #94D58B",
"<X c #99DC8D",
"1X c #94D888",
"2X c #99C595",
"3X c #9CDB93",
"4X c #9CD896",
"5X c #A3DC9D",
"6X c #A3D799",
"7X c #A4CC9D",
"8X c #96E787",
"9X c #9AF88A",
"0X c #9CE392",
"qX c #8DE382",
"wX c #A4E69A",
"eX c #A7FA95",
"rX c #A0F58E",
"tX c #A9C6A6",
"yX c #AAD8A5",
"uX c #B3DBAC",
"iX c #B4D7AB",
"pX c #B7C9B6",
"aX c #B9D8B5",
"sX c #B1C8AC",
"dX c #AAE5A4",
"fX c #B4E6AA",
"gX c #BBE3B6",
"hX c #B6F6AC",
"jX c #C2DCBC",
"kX c #C0C7BD",
"lX c #C4E6BC",
"zX c #CAF7BD",
"xX c #C9D9C7",
"cX c #D1DDCC",
"vX c #D9DCD8",
"bX c #CFCDCC",
"nX c #CAE6C6",
"mX c #D2E6CD",
"MX c #DAE5D7",
"NX c #D9F9D4",
"BX c #CDF6C9",
"VX c #E2EDDB",
"CX c #DDDDE1",
"ZX c #E6DCE7",
"AX c #E7E7E6",
"SX c #EBF5E9",
"DX c #F5EAF5",
"FX c #F7F4F7",
"GX c #EFE0F3",
"HX c #C7C5C6",
/* pixels */
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                                                                                                                                                                                "
"                                                                                                    n N.NXBXNXnX5.K E E ] 9.7.7.m.-X Xm m                                                                                                                       "
"                                                                                                8 *.$.x.gXaXaXaXB./ } | C.Y.H.C.'.nXgXgXnXFXFXFXFXhX>XN.n.x.c.M.M.t.q.G 7                                                                                       "
"                                                                                            8 G J :...c.aXaXaXaX{ ~ ) _ 5.H.V.8.R.pXiXyXsXvXvXCXCX0X9XeXeXeX0XrXeX).z.n.N.                                                                                      "
"                                                                                          M ;.=.F &...z.lXaXgXxX{ L ~ P 5.H.0.6.R.aXpXtXaXCXvXCXvX3XqX8X8X].].:X1Xx.t.z.l.                                                                                      "
"                                                                                      8 e.m.%.F D &.,.1.0.b.l.l.8.B.B.5.8.H.V.8.R.yXyXtXsXvXZXZXAXdXqX<X0X1X1X1X<Xj.O.9.7.                                                                                      "
"                                                                                    n 7.f.i.O.+.D X.,.y.R R E R T.>XE.>XH.B.8.B.H.(.'.>X).M.M.@X@X].{.{.{.).)._.].@XM.M.M.                                                                                      "
"                                                                                    7.] g.p.X.+.r.X.<.y.[ 3.3.#.H.E.R.E.H.5.C.5.V.>XE.'.T.-.-.$.%.[.}.[.{.[.n.L.v.jXGXZXMX                                                                                      "
"                                                                                    :.@.p.w.T &.i.o.&.y.( #.[ [ T.E.E.E.H.B.C.B.H.'.(.'.).h.h.t.1.`.}.{.[.[.[.n.J.aXZXAXAX                                                                                      "
"                                                                                    -.X.p.*.n &.i.O.*.c.3.3.3.[ H.E.E.'.H.Z.C.B.H.(.T.E.R.t.7.t.h.{.}.}.}.[.L./.L.pXZXAXCX                                                                                      "
"                                                                                    &.A e.,.c &.i...,.c.S.C.S.C.' b S ' S *.$.O.l.0X>X,X;Xh.h.h.h.L.`.`.`.K.K.).L.aXZXCXCX                                                                                      "
"                                                                                    &.S e.,.d &.*.z F x.S.S.S.S.b w p w x D Z l u.dXdXdX5Xm.l. Xm.d p d c S F F S kXDXAXAX                                                                                      "
"                                                                                    :.A *.,.w.r.x x ,.j.S.S.C.S.b p z h b D Z M u.dXdXdX4Xm.l.m.c.d w r r C Z C k kXFXSXAX                                                                                      "
"                                                                                    &.>.a.!.^.g.B d F j.S.C.S.S.b p z b S F S C m.dX5XdX4Xl.l.l.k.d p s p V S Z x kXFXAXAX                                                                                      "
"                                                                                    G  X-X Xd.r.f p F x.S.S.S.S.b p d a B Z Z M g.eXyXdX4Xm.m.m.m.A z b b Z F G z bXFXFXDX                                                                                      "
"                                                                                    J OX$Xf.d.e.V *.a.N.G.D.D.S.b r s g 6 : 1 + B qXE.].E.b.0.v.9.q 6 q q x Z n k sXAXMXMX                                                                                      "
"                                                                                    J  X$Xf.p.d.d.+Xs.x.S.S.D.S.c r s b 6 : : + r }.U.U.Y.A.8.C.8.; + : , e w e q n.{.{.1X                                                                                      "
"                                                                                    G .XXX#.1.+XXXs.s.x.S.S.D.S.c t s c 6 : 1 + C }.E.E.Y.8.8.C.0.7 > 1 1 e s e e n.8X].qX                                                                                      "
"                                                                                    e.$Xp.R 1.XXXXf.~.x.Z.S.S.Z.p q w p * X O O e 9X}.}.`.F.A.F.A.% X # : e w e e n.8X8XqX                                                                                      "
"                                                                                    t.$Xi.] 1.OXOXp.w.M.8X1X>X].9.2.;.;.,.H J D *.0.0.b.0.4.4.0.4.e 8 5 3 e t y q N.8XqX1X                                                                                      "
"                                                                                    u.$Xi.] ;.f.t.@.+.N.dXyXyX4X_._.(.[.wXBXhXBX;X= w w w r r w x bXvXbXkXm.O.&.=.L.`.`.`.                                                                                      "
"                                                                                    p.&X!.T T ' @.] &.^.0X3X3X3X).J./.v.,XdXdXhXN.y p p p p p y z cXVXMXVXM.;.z.z.L.G.W.W.                                                                                      "
"                                                                                    q.+X!.E u X.%.@.$.M.0X4X3X3X).J.R.J.,XfXwXhX/.y a s a s p w V xXvXcXxXc.:.:.1.H.I.I.W.                                                                                      "
"                                                                                    q.f.!.i i ' =.#.&.+XwX4X4X4XR.n.N.n.,XfX5XzX/.w z g a b z f A MXSXSXAXu.&.&.*.F.G.D.I.                                                                                      "
"                                                                                    u.d.M.T i ' %.' ,.$XfXiXuXyXx.9.l.x.:.F J p.C 2 5 5 6 6 6 7 q f.^.+X+Xn.v.v.n.>X,X8X1X                                                                                      "
"                                                                                    w.M.p.T j T =.T *.%XgXuXaXuXx.t.k.l.S M C S e + % > @ % % , > y 9 9 9 W.}.Q.W.xXCXvXMX                                                                                      "
"                                                                                    u.i.e.i u T %.b ,.%XjXiXiXyXx.1.k.b.,.C Z J l @ 4 1 1 1 1 > 2 d b p a Y.}.`.U.aXcXmXmX                                                                                      "
"                                                                                    u.i.F h u T =.' ,.#XuX6XiXyXc.9.h.j.,.F F ,.M @ 2 1 1 1 2 > 3 b v z g P.}.U.U.jXvXMXMX                                                                                      "
"                                                                                    u.c.J i u E 2.' F #XlXlXlXjX Xk.x.N.G e M C e : 1 1 1 1 1 > 3 s a r z Y.Q.U.U.jXmXBXmX                                                                                      "
"                                                                                    u.c.e.g i A ' w.w.#XVXmXBXnX;XM.N.2XM X : : > 1 1 1 1 1 1 1 1 2 1 > 3 b.E.L.L.M. XR. X                                                                                      "
"                                                                                    w.r.u.A V G ' w.,.^.NXnXmXlX@Xm.N.;XM + 1 1 1 1 1 1 1 1 1 1 ; > > , 4 b.K.J.H.z.-.9.l.                                                                                      "
"                                                                                    *.,.M.>.B S ..<.,.#XNXmXmXnX@XM. X;XM O 1 1 1 1 > 1 1 1 1 ; > 1 1 , 3 v._.L.R.l.z.l.M.                                                                                      "
"                                                                                    *.e.i.>.n A ' <.,.#XMXnXmXmX XM.N.;XM + : < , + + $ . . . . . : > : 1 J.E.E.T.z.t.h.x.                                                                                      "
"                                                                                    *.,.f.>.S >...~.J 1.{.{.{.`.qXqX1X0XS 7 e 7 Z /.M.f.d.XXXXXXa.q q 6 e 7.v.z.b.n.n.J.R.                                                                                      "
"                                                                                    <.s.oXd.d.p.X.XXD o.Q.W.I.W.8X8X8XeX&.0 t 9 p.zXhXeXzXmXNXNXgXz f z b #.-.$.-.I.{.}.qX                                                                                      "
"                                                                                    1.XX*X+Xd.p.X.XXJ $.}.U.[.W.8X8X8XeX&.7 t 0 ,.hX6X6X6XjXjXlXtXp p r z :.7.-.7.Y.].Q.qX                                                                                      "
"                                                                                    t.XX*X^.!.r.X..XD @.}.{.W.`.9XrX9XeX&.= 0 - &.zXwX6XfXlXjXmXsXw y y p -.4.#.-.`.}.}.9X                                                                                      "
"                                                                                    n.#X=XXXs.p.O.XXF =.Y.L.H.L.L./.R.;X*.e C e ,.6X:X:X2XtXtXsX%Xn n n n :.:.$.:.T.L.L.(.                                                                                      "
"                                                                                    k M H t.X.O.p.,X<X;X:Xn.0.0.0.2.F *.>.%XMXxXvX^.b +.v 2./.9.h.T.,X;X;X;X;X,X:X                                                                                              "
"                                                                                          ;.T ' u.,X0X0X3XY.F.Y.I.b.,.1.O.tXDXMXFX#X' O.S 9.[.F.H.>X0X0X0X0X3XeX:X                                                                                              "
"                                                                                          1.] X.u.,X0X3X<XK.F.H.P.j.<.1.O.%XAXcXVX#Xv O.' 9.).[.J.;X,X>X>X,X,XwX).                                                                                              "
"                                                                                          9.] $.i.0X0X0X0XE.H.H.L.j.<.<.O.%XCXxXZX%X' 2.+.2.[.v.H.(.>X>X>X,XwXeX;X                                                                                              "
"                                                                                          &.g z F ,.:.*.*.v.Y.J.L.b.t.h.-.-XGXvXDX$Xz S G *.z.1.=.:XgXdXfX).7.R.7.                                                                                              "
"                                                                                          V p r C p w t t 9.`.L.L.n.i.k.:.tXDXvXFX&Xe Z Z F &.*.v #XBXlXnXb.T -...                                                                                              "
"                                                                                          S p p Z A B x n j.E.L.K.b.y.k.:.=XGXvXFXoXt Z D D <.&.+.#XBXgXlXN.R 7.@.                                                                                              "
"                                                                                          Z w w Z V z B s 0.W.Y.I.l.u.u.$.sXFXGXFX*XM D D F <.<.S 2XNXBXNXm.E 3.'                                                                                               "
"                                                                                          S b S V V B B s c.).N.N.n.j.j.7.:XgXyXlXM.i ..T O.<.:.O.M.2X@X@X XE.>Xc.                                                                                              "
"                                                                                          ' 9.p.n V B A B a.oXOXOXR.G.P.I.Z.Z.Z.Z.} I ~ I ( 7.4.7.' f a y 2XNXNXiX                                                                                              "
"                                                                                          ..2.,.A A A B n s.$XXXOXN.D.D.P.P.C.S.D. .P ~ P [ 7.;.7.$.V A g 2XBXBX7X                                                                                              "
"                                                                                          ..2.,.n V V B n s.$XOXOXR.I.P.Y.P.S.S.D. .L L I ( t.7.7.>.A A x 7XNXNXuX                                                                                              "
"                                                                                          ] 2.w.A A V V B s.$XXXOXn.D.Y.F.F.S.C.H. .Q ^ / [ 4.4.4.#.A o.T ;XyXyX+X                                                                                              "
"                                                                                          %.;.<.X.A.P.H.P.*.D J G O.#.@.X.4.B.6.B.V.H.A.H.B._ ) ) ) ( ( ( n n G s                                                                                               "
"                                                                                          3.=.r.$.P.Q.Q.Q.$.C G Z ..#.X.X.4.V.6.6.V.H.H.L.B.|  .} ) ( [ ) n C S B                                                                                               "
"                                                                                          3.;.w.@.D.W.P.W.*.Z F D +.#.@.X.4.B.B.8.A.H.A.H.B._ ) } 3.[ ( ) A G S B                                                                                               "
"                                                                                          #.<.w.X.D.G.G.Q.&.M Z C >.#.@.X.4.C.6.5.V.H.H.J.6._ } } ( [ [ [ ..Z >.V                                                                                               "
"                                                                                          #.O.r.&.J.`.K.E.u.e.u.g.=.X.X.O.$.$.=.:.[ _ _ _ ^ / ~ Y { A.B.B.9.g.f.,.                                                                                              "
"                                                                                          ] =.r.w.).;X@X). XM. X X1...O.X.>.S S F R I Q L ~ ~ Y L 5.A.6.C.t.g.M.e.                                                                                              "
"                                                                                          3.=.r.<.N./.).).M.d.M.M.:.' O.>.O.+.+.*.R W W ~ ~ ~ ~ ~ { A.B.B.t.g.i.,.                                                                                              "
"                                                                                          #.&.r.2./.).).).i.e.u.s.*.v ....A A b V R I | ~ / ~ ~ P { 0.B.B.t.e.f.,.                                                                                              "
"                                                                                          ' S u.*./.).).R.@X+X@X#X9.#.7.4.9.c.x.^.4.L ~ ! ! / ! ! 5.H.V.6.).:X0X/.                                                                                              "
"                                                                                          ' S r.Z v.L.v.v.6XgXaXaX].S.H.F.].dXdXhXv.K ! ! ! ! ^ ! 6.v.V.8.>X0XeX).                                                                                              "
"                                                                                          ..S r.S v.L.H.0.4XaXuXaX_.A.A.A.].5X<XyX8.K ! R ! ! ^ ! 5.8.8.8.'.3XdX).                                                                                              "
"                                                                                          A S w.S b.L.H.0.6XgXaXjX'.A.H.S._.4X<XdX8.K L E ~ ~ ~ P B.V.6.B.'.4X0X).                                                                                              "
"                                                                                          >.t.,.S b.H.v.v.7XaXyXuX).V.A.0._.5X<XyXV._ [ [ ( ( ] ( 9.^.c.M.,X0XwX/.                                                                                              "
"                                                                                          <.f.r.~.).].1X<Xc.=.1.:.:.4.%.@./.3X1X,XY.S.D.G.9.&.2.O.~.oXOXOX:X8XdX).                                                                                              "
"                                                                                          <.y.r.^.<XwX6XwX:.' O.@.#.-.-.X.J.3X1X<XK.C.S.D.7.O.%.$.d.&XXXXX,X0XwX;X                                                                                              "
"                                                                                          :.f.p.d.1X0X<X6X9.' =.$.=.%.3.] n.0X1X1XK.Z.F.S.4.+.O.X.d.&X!.XX6XwXhX:X                                                                                              "
"                                                                                          F ,.,.^.0X0X0XrX;.b ....X.#.#.@.R.<X,X6XY.Z.S.S.0.2.7.4.d.XXXX!.^.n.T.9.                                                                                              "
"                                                                                          Z Z x F %X%X%X#X%X7X=XsX6X6X6X6X5X5XyXyX`.Z.F.S.L.).T._.^.~.!.!.+.' ] A                                                                                               "
"                                                                                          Z D z z ~.OX|.|.cXSXVXAXlXlXlXlXfXyXwXuX_.Z.S.S.Y.).T.).^.~.XX!.2.X.%.+.                                                                                              "
"                                                                                          D D x A .XoX.X.XkXMXnXcXjXfXfXuXfX5XyXfX'.Z.S.S.H.).R.T.d.a.s.~.&.$.%.+.                                                                                              "
"                                                                                          O.b x V .XoXOXOXbXSXAXAXmXjXlXlXuX5X5XyXU.Z.S.F.L.R.K.K.+XOX&X&X2.X.;.>.                                                                                              "
"                                                                                          ] ` T S .XoXOX.XtXtX7X2X,X8X8X].wXuXdXyX1X].1X1X[.H.n.0.yXjXjXjX1.' 2.+.                                                                                              "
"                                                                                          ] i ] $.s.!.s.!.O.T T g 6.G.S.Z.].uX5X5X5X4X4X6X).0.v.0.yXlXjXaX2.' %.+.                                                                                              "
"                                                                                          ] ` T O.~.!.s.!.=.X.@.+.A.W.D.D.1XfX5XdX6X<X6X4X).0.L.v.yXaXgXaX*.' $.v                                                                                               "
"                                                                                          T E T X.~.!.~.s.=.%.O.+.F.Q.W.G.8XuX5XwX6X,X,X<X).v.H.H.tXjXaXiX1.$.9.&.                                                                                              "
"                                                                                          E i g O.~.~.~.XX2.] @.X.0.F.A.6.>XdX5XyX<X,X<X3Xn.7.;.-.;X4X<X,XH.H.E.n.                                                                                              "
"                                                                                          R E n ' /.6X].,X;.v ] ' ' v g h N.fX5X5X<X1X,X<Xj.$.%.-.E.0X,X,XJ.n.`.j.                                                                                              "
"                                                                                          T i n ' ].wX<X0X%.' ' @.' ' ..g N.dXwX4X4X,X,X0Xb.%.;.-.).0X<X<XJ.v.[.b.                                                                                              "
"                                                                                          E E g ' ].3X1X<X7.g ] X.' g ' h R.hXdXdX1X].>X1X9.#.-.-.>X0X,X,XJ.v.Y.j.                                                                                              "
"                                                                                          ` T A ' 1XwX3XwX%.T o.' ........N.5X2X:X6XyXyXuXN.;.k.z.l.x.c.z.0.A.F.9.                                                                                              "
"                                                                                          E T &.b v./.n.b.8.4.8.6.c..X!.d.XX.X~.a.=XMXxXMX#Xz.M.M.t.<.<.1.0.A.F.8.                                                                                              "
"                                                                                          ` T &.g #.#.#.o.8.H.V.C.^.OXXXXX~. Xd.s.=XmXxXcX#Xt.m.m.y.t.y.z.0.8.D.4.                                                                                              "
"                                                                                          R ..+.g #.-.-.-.8.A.8.B.c.XX!.XXXX!.XX~.pXMXxXmX&X<.m.m.y.h.y.1.0.A.F.9.                                                                                              "
"                                                                                Z !.J H =.1.m.O.g X.#.#.@.8.V.8.V.i..X!.!.!.XXs.a.tXlXiXfX).v.L.R.z.t.k.c.,X5XwX:X                                                                                              "
"                                                                                D #X,.H S 1.^.g.+.%.b.j.j.0.V.V.B.#XsX7XiXi.B G C N.}.{.{.`.W.`.W.j.h.h.c.5XuXzX%X                                                                                              "
"                                                                                N /.] ,.&.1.!.r.p.:X0X<X6XH.B.A.B.6XlXjXnXu.t V r N.9X{.].[.I.W.W.l.y.t.k.5XyXhX:X                                                                                              "
"                                                                                D ^.@.p.4.( ~.g.r.].8X1X<XA.B.V.B.,XjXyXlXr.p V k ).9X8X}.}.I.}.Q.b.z.9.b.fXfXfX6X                                                                                              "
"                                                                                M c.#.g.4.U ( r.g.;X6X<X1XF.B.B.{ :XjXiXmXs.k V C R.}.`.[.H.L.[.R.c.u.r.r.i.p.w.,.D                                                                                             "
"                                                                                l 9.] g.4.I U ~ 2.:X<X>X:XH.0.v.1XjXSXjXV.( ! / / n.H k k N N D Z N M Z D C C C Z H ,.N                                                                                         "
"                                                                                M 9.' e.7.I W W W } } ) m.c.g.&XbXbXHXoXj E R [ ] e.H  XOX$X=XH 8 t x z Z S A B b D H a.H k                                                                                     "
"                                                                                l 9.' H 3.W ~ W { h.#.%.w.e.X.X.T E E R [ [ =.a.a.e.g.mXMXMXSXH N H H D V C V V B x V F g.XXXXF                                                                                 "
"                                                                                q 2.] ,.7.I W I 5.*Xe.X.w.f.~ I P I |  . . .{ f.g.u.i.aXmXcXMX&XJ w.<.@.] [ 3.( =.g.u.*.=XMXMXSX                                                                                "
"                                                                                6 ,.<.a.3.I W U ( OX:.@.:.i.^ P ~ Q _  . . .6.p.f.u.g.pXcXxXMX@XL P I P }  .} } z.s.i.u.tXMXcXSX                                                                                "
"                                                                                6 $.^.H ] _ ( ! n.$X<.@.:.s._ W / Q ) 5. .} 5.g.u.g.<.pXvXxXCX%XL P Y ~ ) } ) ) h.f.g.e.-XmXcXVX                                                                                "
"                                                                                e 2.f.F T 8.3.3.tX$X=.] <.d.( P W Q ^  .) ) ) m.f.m.t.pXMXvXGX2XL L Y ~ ) B. .} h.g.i.q.tXvXcXMX                                                                                "
"                                                                                t j.^.,.T 4.3.3.2X^.O.' >.s.( I ! W ^ ^ ^ / ^ l.M.l.h.pXAXvXDXtXL Y ~ ! )  .) ) h.M.m.t.sXAXvXAX                                                                                "
"                                                                                e j.&XH T [ R R 7X@XX.T >.f.( W / W ~ ^ _ W ^ l.M.m.h.tXAXcXGXtXL Y ~ ~ ^ ^ / ~ z.M.l.h.aXGXvXSX                                                                                "
"                                                                                l j.&Xs.4.H.H.H.;Xf.$.' o.a.3.I ~ ~ ^ ^ ^ ~ ^ l. Xb.-.tXGXCXDXpXL Q W ~ ^ ^ / ~ 9. Xl.h.pXAXvXFX                                                                                "
"                                                                                k n.XXw.A.rXrXeX/.r.%.' v a.4.I P W ~ L L U U :. XM.h.-XAXxXvXyXQ Q W ~ ^ _ ^ W 8. Xm.h.kXFXGXFX                                                                                "
"                                                                                k 9.OXa.0.9X{.}.).,.' $.*.g.3.P ^ ! ^ 8.H.H.T.T.P.L.P.E.(.[.(.L.Q Q W W L U L Q b.M.x.l.sXnXfXnX                                                                                "
"                                                                                k j.OXw.L.eXrX9X:XS b p.XXG ] 5.3.( 7.mXMXMXCX0XG.W.W.Y.[._._.K.) ! ^ ( R.>X:X5XE.P.I.U.Y.K.Y.W.                                                                                "
"                                                                                k j.OX~.%.b.2.%.M M +.<.XXA T 7.4.[ 3.aXxXxXxX,XD.Y.U.Y.)._._.).4.3.3.7.cXAXMXvXqXD.I.I.Y.).`.{.                                                                                "
"                                                                                k 2.OX^.f 9 y y @ l &.<.OXA T 3.3.3.-.iXmXgXnX0XD.Y.I.Y.).[._._.4.3.[ 3.aXnXjXjX].D.Y.I._.(._.8X                                                                                "
"                                                                                k ,.~.&Xb w x d ; l =.<.XXS g 3.#.R ] iXMXnXmX5XD.U.I.Y._.)._.].8.#.] 3.jXmXnXmX].D.U.Y.[._._.8X                                                                                "
"                                                                                k <..X!.v a g v 2 k j.1.$X,.T 8.8.8.H.:X-X#X X;X`.`.]._.).].).:X4.] [ 7.iXjXsXtX`.U._._._.).].0X                                                                                "
"                                                                                ; F &XH 0 0 6 5 0 +.y.y.*Xp.4.8XqX9X9XJ.q.m.u.N.{.]._._.(.).].(.).Y.{.`.M.m.m.u.).`.`._.'.).].<X                                                                                "
"                                                                                  7 OXa.* , , + q $.2.<.oXg.4.8XqXqX8X Xm.m.f.N.`.`.`.].(.(.].:X8X9X8X8Xc.f.f.M._.{.`.].].).].0X                                                                                "
"                                                                                    M D 7 1 1 > q ' 2.z.$Xs.%.{.qX{.8X). XM.M.N.8X{.8XqX8X0X1X(.].{.{.].N. XM.M.].{.{.8X0XrX8XrX                                                                                "
"                                                                                      * 5 1 4 4 l 2.z.2.oX~.#.8XeX9X9X>Xm.M.f.i.J.0.0.9.S M k > ,.eXeX9X@XN. XM.R.[.n.0.,.F C C                                                                                 "
"                                                                                        X X . o o 7 y.2.OXXX@.v.v.7.9.V 8 8 3 3 r r w y % + + X x _.b.1.n m 8 8 s d w w @ + + ,                                                                                 "
"                                                                                                    y.2.OXoX&.w 0 y y 7 + @ + 1 r p p z 6 , 2 , 5 w w 0 # + + # w p s p 3 > > 3                                                                                 "
"                                                                                                    p.2.XXoXO.z r p b e : 1 1 1 p a p g 6 , > , 7 z a r 1 > > 4 r d a z 3 , @ 4                                                                                 "
"                                                                                                    2.2.XXoX=.d r p g t > > : , r v z v q @ 2 1 6 a b x > , , > a b z s 5 1 7 l                                                                                 "
"                                                                                                    <.+.a.*X,.v a z A t 1 4 5 6 q q q 5 0 p r a a s z t 3 5 0 q 6 6 5 3 w z a ..                                                                                "
"                                                                                                    p.S  XOXx w 6 6 2 6 p p a c 3 , > + 6 b z z p 7 > 3 p b b z 1 , , > p z s A                                                                                 "
"                                                                                                    c.*.a.oXe ; , , , 2 d d p d 8 , 1 > 6 b f z p > : 2 a a a s 3 1 > 1 r c d v                                                                                 "
"                                                                                                    Z ,.a.*Xr 2 , 2 , 3 p d p b 6 , 1 , 7 a f z g 3 @ 3 a a b f 1 > 4 4 r d s S                                                                                 "
"                                                                                                      e g.=XN 5 > 1 % 1 z v c ' e 4 4 1 8 S +.x l 3 1 5 x a B A e 1 ; 1 & X o $                                                                                 "
"                                                                                                          J D 6 2 1 5 8 0 0 0 e e 2 . . # ; 6 3 . 1 5 @ o o $ * * X                                                                                             "
"                                                                                                                                                                                                                                                                "
};