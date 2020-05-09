P -> program <identifier>; VDB MB | VDB MB
VDB -> <empty> | var VD+
VD -> <identifier> (,<identifier>)* : <type>;
MB -> begin (S)* end.
S -> FO | WH | IF | AS | CS | WR
WR -> writeln(<identifier> | <unsigned_constant>);
CS -> begin (S)* end;
AS -> <identifier> := E;
E -> SE (RO SE)*
RO -> = | <> | < | > | <= | >=
SE -> SI? T (SI T)*
SI -> + | -
T -> F (MO F)*
MO -> / | * | div | mod
F -> <identifier> | <unsigned_constant> | (E)
IF -> if E then S | if E then S else S
WH -> while E do S
FO -> for <identifier> := FL do S
FL -> E to E | E downto E