program fld;
var x,y:int64;
procedure setup;
begin
  assign(input,'fld.in');
  reset(input);
  assign(output,'fld.out');
  rewrite(output);
end;
procedure endit;
begin
  close(input);
  close(output)
end;
begin
  setup;
  readln(x,y);
  writeln(trunc((x*x+y*y)*pi/2/50));
  endit;
end.

