#include "HPLC/parser.h"

extern "C" const TSLanguage* tree_sitter_hplc(void);

namespace
{
SourceSpan spanFor(TSNode node, const SourceCode& sourceCode)
{
  const TSPoint start = ts_node_start_point(node);
  const TSPoint end = ts_node_end_point(node);
  return {sourceCode.name, ts_node_start_byte(node), ts_node_end_byte(node), start.row, start.column, end.row, end.column};
}
}

ParseResult HPLCParser::parse(const SourceCode& sourceCode) const
{
  TSParser* parser = ts_parser_new();
  ts_parser_set_language(parser, tree_sitter_hplc());
  TSTree* tree = ts_parser_parse_string(parser, nullptr, sourceCode.contents.data(), sourceCode.contents.size());
  ts_parser_delete(parser);

  ParseResult result;
  result.tree = std::shared_ptr<TSTree>(tree, ts_tree_delete);
  TSNode root = ts_tree_root_node(tree);
  if (ts_node_has_error(root))
    result.diagnostics.push_back({"syntax error", spanFor(root, sourceCode)});
  return result;
}
