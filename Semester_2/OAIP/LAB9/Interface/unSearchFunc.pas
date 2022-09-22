unit unSearchFunc;

interface
uses
  unTypes, Vcl.ComCtrls, Vcl.StdCtrls;

procedure PrintSearchedTime(head, tail: TElem; lv: TlistView; dtp: TDateTimePicker; receiveDateOption: boolean);
procedure PrintSearchedGroup(head, tail: TElem; lv: TlistView; cb:TComboBox);

implementation
uses
  ufAdd, unListFunc, System.SysUtils;

//Return true if date1 and date2 equal
function areEqualDates(date1, date2: TDate): boolean;
begin
  if (date1.day = date2.day) and (date1.month = date2.month) and (date1.year = date2.year) then
    areEqualDates := true
  else
    areEqualDates := false;
end;

//Print in listView appliance, if dates matched
procedure PrintSearchedTime(head, tail: TElem; lv: TlistView; dtp: TDateTimePicker; receiveDateOption: boolean);
var
  item: TListItem;
  date1: TDate;
  date2: TDate;
begin
  lv.Clear;
  date1 := GetDate(FormatDateTime('dd.mm.yyyy', dtp.Date));
  tail := tail^.prev;
  while not (tail^.prev = nil) do
  begin
    if receiveDateOption = true then
      date2 := tail^.appliance.receiveDate
    else
      date2 := tail^.appliance.returnDate;
    if areEqualDates(date1, date2) then
    begin
      item := lv.Items.Add;
      item.caption := OutputGroup(tail^.appliance.group);
      item.SubItems.Add(OutputBrand(tail^.appliance.brand));
      item.SubItems.Add(tail^.appliance.receiveDate.day + '.' + tail^.appliance.receiveDate.month + '.' + tail^.appliance.receiveDate.year);
      item.SubItems.Add(tail^.appliance.returnDate.day + '.' + tail^.appliance.returnDate.month + '.' + tail^.appliance.returnDate.year);
      item.SubItems.Add(OutputCondition(tail^.appliance.isReady));
    end;
    tail := tail^.prev;
  end;
end;

//Print in listView appliance, if groups matched
procedure PrintSearchedGroup(head, tail: TElem; lv: TlistView; cb:TComboBox);
var
  item: TListItem;
  group1: TGroup;
  group2: TGroup;
begin
  lv.Clear;
  group1 := GetGroup(cb.ItemIndex);
  tail := tail^.prev;
  while not (tail^.prev = nil) do
  begin
    group2 := tail^.appliance.group;
    if group1 = group2 then
    begin
      item := lv.Items.Add;
      item.caption := OutputGroup(tail^.appliance.group);
      item.SubItems.Add(OutputBrand(tail^.appliance.brand));
      item.SubItems.Add(tail^.appliance.receiveDate.day + '.' + tail^.appliance.receiveDate.month + '.' + tail^.appliance.receiveDate.year);
      item.SubItems.Add(tail^.appliance.returnDate.day + '.' + tail^.appliance.returnDate.month + '.' + tail^.appliance.returnDate.year);
      item.SubItems.Add(OutputCondition(tail^.appliance.isReady));
    end;
    tail := tail^.prev;
  end;
end;

end.
