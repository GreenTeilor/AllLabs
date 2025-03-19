library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_latch_async_reset is
    Port ( d, rst : in STD_LOGIC;
           q, nq : out STD_LOGIC);
end D_latch_async_reset;

architecture Behavioral of D_latch_async_reset is
attribute dont_touch : string;
attribute dont_touch of Behavioral : architecture is "true";
signal q_int : STD_LOGIC;
begin					   
    process(d, rst)
    variable r, s, rst_var : STD_LOGIC;
    begin
        s := d;
        r := not d;
        rst_var := rst;
        if (rst_var = '0') then
            if s = '1' and r = '0' then
                q_int <= '1';
            elsif s = '0' and r = '1' then
                q_int <= '0';
            end if;
        else
            q_int <= '0';
        end if;
    end process;

    q <= q_int;
    nq <= not q_int;
end Behavioral;
