Program	tsoi_standard;
{ tsoi2 War }

Const
inf	='war.in';
ouf	='war.out';
LimitN	=30000;

Var
hp	:array[1..LimitN]of longint;
treap	:array[0..LimitN]of longint;
l,r	:array[0..LimitN]of longint;
aux	:array[0..LimitN]of longint;
count	:array[0..LimitN]of longint;
n,m	:longint;
size	:longint;
i,k,x	:longint;
root	:longint;
free	:longint;
c	:char;

procedure	rotate_r(var i:longint);
var
j	:longint;
begin
	j:=l[i];
	l[i]:=r[j];
	r[j]:=i;
	count[j]:=count[i];
	count[i]:=count[l[i]]+count[r[i]]+1;
	i:=j;
end;

procedure	rotate_l(var i:longint);
var
j	:longint;
begin
	j:=r[i];
	r[i]:=l[j];
	l[j]:=i;
	count[j]:=count[i];
	count[i]:=count[l[i]]+count[r[i]]+1;
	i:=j;
end;

procedure	insert(var i:longint;x:longint);
begin
	if i=0 then
	begin
		if free=0 then
		begin
			inc(size);
			i:=size;
		end
		else
		begin
			i:=free;
			free:=0;
		end;
		treap[i]:=x;
		aux[i]:=random(65535);
		count[i]:=1;
		l[i]:=0;
		r[i]:=0;
	end
	else
	if x<treap[i] then
	begin
		insert(l[i],x);
		inc(count[i]);
		if aux[l[i]]>aux[i] then
			rotate_r(i);
	end
	else
	begin
		insert(r[i],x);
		inc(count[i]);
		if aux[r[i]]>aux[i] then
			rotate_l(i);
	end;
end;

function	query(k:longint):longint;
var
i	:longint;
begin
	i:=root;
	while true do
		if k<count[r[i]]+1 then
			i:=r[i]
		else
		if k>count[r[i]]+1 then
		begin
			dec(k,count[r[i]]+1);
			i:=l[i];
		end
		else	exit(treap[i]);
end;

procedure	do_remove(var i:longint);
begin
	dec(count[i]);
	if l[i]=0 then
	begin
		free:=i;
		i:=r[i];
	end
	else
	if r[i]=0 then
	begin
		free:=i;
		i:=l[i];
	end
	else
	if aux[l[i]]>aux[r[i]] then
	begin
		rotate_r(i);
		do_remove(r[i]);
	end
	else
	begin
		rotate_l(i);
		do_remove(l[i]);
	end;
end;

procedure	remove(var i:longint;x:longint);
begin
	if x<treap[i] then
	begin
		dec(count[i]);
		remove(l[i],x);
	end
	else
	if x>treap[i] then
	begin
		dec(count[i]);
		remove(r[i],x);
	end
	else	do_remove(i);
end;

Begin
	randomize;
	assign(input,inf);
	reset(input);
	assign(output,ouf);
	rewrite(output);
	read(n);
	for i:=1 to n do
	begin
		read(hp[i]);
		insert(root,hp[i]);
	end;
	readln(m);
	for i:=1 to m do
	begin
		read(c);
		if c='A' then
		begin
			readln(k,x);
			remove(root,hp[k]);
			dec(hp[k],x);
			if hp[k]>0 then
				insert(root,hp[k])
			else	dec(n);
		end
		else
		if c='C' then
		begin
			readln(k,x);
			remove(root,hp[k]);
			inc(hp[k],x);
			insert(root,hp[k]);
		end
		else
		begin
			readln(k);
			if k>n then
				writeln(-1)
			else	writeln(query(k));
		end;
	end;
	writeln(n);
	close(input);
	close(output);
End.
