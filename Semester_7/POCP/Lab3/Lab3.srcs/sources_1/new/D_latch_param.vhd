library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity D_latch_param is
	port (
		d : in std_logic;
		q, nq : out std_logic
	);
end D_latch_param;

architecture Param of D_latch_param is
attribute dont_touch : string;
attribute dont_touch of Param : architecture is "true";
signal q_int, qn_int : STD_LOGIC;
begin					   
    process(d)
    variable r, s : STD_LOGIC;
    begin
        s := d;
        r := not d;
        if s = '1' and r = '0' then
            q_int <= '1' after 3ns;
        elsif s = '0' and r = '1' then
            q_int <= '0' after 3ns;
        end if;
    end process;

    q <= q_int;
    nq <= not q_int;
end Param;