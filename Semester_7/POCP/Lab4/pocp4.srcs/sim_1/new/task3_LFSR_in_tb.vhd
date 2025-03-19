library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_LFSR_in_tb is
    Generic(N : integer := 3;
    alpha : std_logic_vector := "1101"
    );
end task3_LFSR_in_tb;

architecture Behavioral of task3_LFSR_in_tb is
component task3_LFSR_In     
generic (N : integer := 3;
init_state : std_logic_vector := "111";
alpha : std_logic_vector := "1101");
port(
CLK: in std_logic;
RST: in std_logic;  
Pout: out std_logic_vector(alpha'high - 1 downto 0)
);
end component;
signal CLK: std_logic := '0';
signal RST: std_logic := '0'; 

signal Pout: std_logic_vector(alpha'high - 1 downto 0);
constant clock_period: time := 10 ns;
begin
 uut: task3_LFSR_In port map (CLK => CLK, RST => RST, POut => POut);
 CLK <= not CLK after clock_period;
end Behavioral;
