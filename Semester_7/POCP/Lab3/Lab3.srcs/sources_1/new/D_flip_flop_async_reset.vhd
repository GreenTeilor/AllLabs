library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_flip_flop_async_reset is
    Port ( d, clk, rst : in STD_LOGIC;
           q : out STD_LOGIC);
end D_flip_flop_async_reset;

architecture Behavioral of D_flip_flop_async_reset is
signal s: STD_LOGIC;
begin
    process(d, clk, rst)
    begin
        if (rst = '1') then
            s <= '0';
        elsif (rising_edge(CLK)) then
            s <= d;
        end if;
    end process;
    q <= s;
end Behavioral;
