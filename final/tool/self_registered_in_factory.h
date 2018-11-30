#pragma once

//with below line we promise that definition of class WILL BE included in some files
//this is 'Forward declaration': https://en.wikipedia.org/wiki/Forward_declaration
class block_factory;

//template <typename TBlock, typename ...Ts>
template <typename TBlock>
class self_registered_in_factory
{
protected:
  //because it is static member, it will be initialized in the moment when template is compiled
  //template is compiled when concrete class (which is derived from SelfRegisteredInFactory class) is instantiated (before main method)
  static bool is_blocktype_registered_;
public:
  static std::string GetBlockTypeName() { return TBlock::name; }
  static std::string GetDescription() { return TBlock::description; }
};

//this is implementation of assignment of static variable is_blocktype_registered_ which is triggered before 'main'.
template <typename TBlock>
bool self_registered_in_factory<TBlock>::is_blocktype_registered_ =
block_factory::register_block(TBlock::GetBlockTypeName(), TBlock::GetDescription(), TBlock::CreateMethod);
