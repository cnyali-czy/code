Program	tsoi_standard;
{ TSOI Exercise }

Const
inf	='exercise.in';
ouf	='exercise.out';
LimitT	=1440;

Var
d	:array[1..LimitT]of longint;
n,m,k	:longint;
i,j,a,b	:longint;
c	:char;

Begin
	assign(input,inf);
	reset(input);
	assign(output,ouf);
	rewrite(output);
	readln(n,m);
	for i:=1 to LimitT do
		d[i]:=1;
	for i:=1 to m do
	begin
		repeat
			read(c);
		until	c=' ';
		readln(a,b,k);
		for j:=a to b do
			dec(d[j],k);
	end;
	for i:=1 to LimitT do
	begin
		inc(n,d[i]);
		if n<=0 then
		begin
			writeln('Runtime Error');
			writeln(i);
			close(output);
			halt;
		end;
	end;
	writeln('Accepted');
	writeln(n);
	close(output);
End.
