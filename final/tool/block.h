#pragma once
#include <string>
#include <vector>
#include <map>
#include "self_registered_in_factory.h"

class block
{
public:
  block(std::string block_type_name, int number_of_parameters, const std::vector<double>& parameters);
  virtual ~block() = default;
  virtual double calc(double input) = 0;
  std::string get_command();
protected:
  std::vector<double> parameters_;
private:
  std::string block_type_name_;
};

//holder for block meta data: description and create method
class block_meta
{
public:
  using TBlockCreateMethod = std::unique_ptr<block>(*)(const std::vector<double>& parameter);
  block_meta(std::string description = "", TBlockCreateMethod block_create_method = nullptr)
  {
    description_ = description;
    block_create_method_ = block_create_method;
  }
  TBlockCreateMethod GetCreateMethod() const
  {
    return block_create_method_;
  }
  std::string Getdescription() const
  {
    return description_;
  }

private:
  std::string description_;
  TBlockCreateMethod block_create_method_;
};

class block_processor
{
private:
  std::vector<std::unique_ptr<block>> blocks_;
public:
  block_processor();
  void add_block(std::unique_ptr<block> &b);
  double calc_all(double input) const;
  using sequence_list = std::vector<std::pair<std::string, std::vector<double>>>;
  void load(sequence_list sl);
  bool remove_block(unsigned int index);
  std::vector<std::string> get_sequence();
};

//prevent class derivation with 'final'
class block_factory final
{
public:
  using TBlockCreateMethod = std::unique_ptr<block>(*)(const std::vector<double>& parameter);
  //prevent class instantiation
  block_factory() = delete;
  //all members are static
  //wrap static methods in this separate class because I want to have it in one place and 'create_methods_' has to be hidden
  static bool Register(const std::string block_name, const std::string block_description, TBlockCreateMethod funcCreateBlock);
  static std::unique_ptr<block> Create(const std::string& block_name, const std::vector<double>& parameters);
  static std::vector<std::string> GetBlockTypes();
private:
  static std::map<std::string, block_meta> create_methods_;
};