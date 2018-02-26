Program	tsoi_standard;
{ TSOI cmdo }

Const
inf	='cmdo.in';
ouf	='cmdo.out';
LimitN	=15;
LimitM	=60;
LimitS	=(1 shl LimitN)-1;
dirs	=4;
dy	:array[1..dirs]of shortint=(1,0,-1,0);
dx	:array[1..dirs]of shortint=(0,1,0,-1);
e	:array[1..LimitN]of longint=
	(1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384);

Var
f	:array[0..LimitS]of int64;
g	:array[1..LimitN,1..LimitN]of boolean;
x	:array[1..LimitM,1..LimitM]of char;
id	:array[1..LimitM,1..LimitM]of shortint;
n,s,w,h	:longint;

function	is_enemy(x:char):boolean;
begin
	is_enemy:=(x='<')or(x='^')or(x='>')or(x='v');
end;

function	calc_dir(x:char):shortint;
begin
	if x='v' then exit(1);
	if x='>' then exit(2);
	if x='^' then exit(3);
	calc_dir:=4;
end;

function	inrange(ty,tx:integer):boolean;
begin
	inrange:=(ty>0)and(ty<=h)and(tx>0)and(tx<=w)and(x[ty][tx]<>'#');
end;

procedure	init;
var
i,j	:longint;
begin
	assign(input,inf);
	reset(input);
	readln(h,w);
	for i:=1 to h do
	begin
		for j:=1 to w do
		begin
			read(x[i][j]);
			if is_enemy(x[i][j]) then
			begin
				inc(n);
				id[i][j]:=n;
			end;
		end;
		readln;
	end;
	close(input);
	s:=(1 shl n)-1;
end;

procedure	build;
var
i,j,d,k	:longint;
ty,tx	:longint;
begin
	for i:=1 to h do
	for j:=1 to w do
		if is_enemy(x[i][j]) then
		begin
			d:=calc_dir(x[i][j]);
			ty:=i;
			tx:=j;
			repeat
				inc(ty,dy[d]);
				inc(tx,dx[d]);
				if not inrange(ty,tx) then
					break;
				if is_enemy(x[ty][tx]) then
					g[id[i][j]][id[ty][tx]]:=true;
			until	false;
		end;
end;

procedure	solve;
var
i,j,k	:longint;
ok	:boolean;
begin
	f[0]:=1;
	for i:=1 to s do
	begin
		for j:=1 to n do
		if i and e[j]>0 then
		begin
			ok:=true;
			for k:=1 to n do
			if (i and e[k]>0)and g[k][j] then
			begin
				ok:=false;
				break;
			end;
			if ok then
				inc(f[i],f[i and not e[j]]);
		end;
	end;
end;

procedure	show;
begin
	assign(output,ouf);
	rewrite(output);
	if f[s]=0 then
		writeln('Impossible')
	else	writeln(f[s]);
	close(output);
end;

Begin
	init;
	build;
	solve;
	show;
End.
