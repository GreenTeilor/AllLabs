library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_flip_flop_enable is
    Port ( d, clk, e : in STD_LOGIC;
           q, nq : out STD_LOGIC);
end D_flip_flop_enable;

architecture Behavioral of D_flip_flop_enable is
signal q_t : std_logic;
begin
Main: process(d, clk, e)
begin
    if rising_edge(clk) then
        if e = '1' then
            q_t<=d;
        end if;
    end if;    
end process;
q<=q_t;
nq<= not q_t;
end Behavioral;
