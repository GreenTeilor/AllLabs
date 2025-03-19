----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 15.09.2024 20:09:29
-- Design Name: 
-- Module Name: simple_function - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity simple_function is
    Port ( IN1 : in STD_LOGIC;
           IN2 : in STD_LOGIC;
           IN3 : in STD_LOGIC;
           Q : out STD_LOGIC);
end simple_function;

architecture Behavioral of simple_function is

begin
    Q <= (IN1 and IN2) or (IN3 and not IN2);
end Behavioral;
