program tsoi2_exercise;
// By Erwin
const
  fi='exercise.in';
  fo='exercise.out';

var
  ch:char;
  n,m,i,j:longint;
  start,ed,cost:longint;
  delta:array[1..1440] of longint;
  died:boolean;

begin
  assign(input,fi);
  reset(input);
  assign(output,fo);
  rewrite(output);
  for i:=1 to 1440 do
    delta[i]:=1;
  readln(n,m);
  for i:=1 to m do
    begin
      repeat
        read(ch);
      until ch=' ';
      readln(start,ed,cost);
      for j:=start to ed do
        dec(delta[j],cost);
    end;
  died:=false;
  for i:=1 to 1440 do
    begin
      inc(n,delta[i]);
      if n<=0 then
        begin
          writeln('Runtime Error');
          writeln(i);
          died:=true;
          break;
        end;
    end;
  if not died then
    begin
      writeln('Accepted');
      writeln(n);
    end;
  close(output);
  close(input);
end.
