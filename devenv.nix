{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = [ pkgs.git ];
  languages.cplusplus = {
    enable = true;
  };

  # https://devenv.sh/pre-commit-hooks/
  pre-commit.hooks = {
    # format C++ code
    clang-format.enable = true;
  };

}
