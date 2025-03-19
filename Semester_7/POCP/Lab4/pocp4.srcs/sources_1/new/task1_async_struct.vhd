library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task1_async_struct is
    Generic(n : integer := 4);
    Port ( Din : in STD_LOGIC_VECTOR(n-1 downto 0);
           EN : in STD_LOGIC;
           Dout : out STD_LOGIC_VECTOR(n-1 downto 0));
end task1_async_struct;

architecture Behavioral of task1_async_struct is
component D_latch
        port(
        D, EN : in std_logic;
        Q: out std_logic);
end component;
begin
    reg: for i in n-1 downto 0 generate
        DI: D_latch port map(D => Din(i), EN => EN, Q => Dout(i));
    end generate;
end Behavioral;
