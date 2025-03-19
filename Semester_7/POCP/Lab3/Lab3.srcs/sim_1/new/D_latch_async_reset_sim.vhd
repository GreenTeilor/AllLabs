library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_latch_async_reset_sim is
end D_latch_async_reset_sim;

architecture Behavioral of D_latch_async_reset_sim is

component D_latch_async_reset
    Port ( d, rst : in STD_LOGIC;
       q, nq : out STD_LOGIC);
end component;
signal d : STD_LOGIC := '0';
signal rst : STD_LOGIC := '0';
signal q : STD_LOGIC;	
signal nq : STD_LOGIC;  
constant res_clock_period : time := 10 ns;
begin
U1 : D_latch_async_reset
    port map (
        d => d,
        rst => rst,
        q => q,
        nq => nq
    );

d <= not d after res_clock_period * 4;
rst <= not rst after res_clock_period;
end Behavioral;
