
// Generated from Dap.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "DapVisitor.h"


/**
 * This class provides an empty implementation of DapVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  DapBaseVisitor : public DapVisitor {
public:

  virtual std::any visitParse(DapParser::ParseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSas_stmt_list(DapParser::Sas_stmt_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_stmt(DapParser::If_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_then_else_stmt(DapParser::If_then_else_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDelete_stmt(DapParser::Delete_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(DapParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(DapParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOf_var_list(DapParser::Of_var_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifiers_list(DapParser::Identifiers_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIn_var_list(DapParser::In_var_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitColonInts(DapParser::ColonIntsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(DapParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariables(DapParser::VariablesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbort_main(DapParser::Abort_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbort_stmt(DapParser::Abort_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFile_spec(DapParser::File_specContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProc_main(DapParser::Proc_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProc_stmt(DapParser::Proc_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProc_name(DapParser::Proc_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_main(DapParser::Array_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_stmt(DapParser::Array_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_name(DapParser::Array_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_subscript(DapParser::Array_subscriptContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_elements(DapParser::Array_elementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitial_value_list(DapParser::Initial_value_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitial_value_list_item(DapParser::Initial_value_list_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitial_value_list_bk(DapParser::Initial_value_list_bkContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstant_iter_value(DapParser::Constant_iter_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstant_value(DapParser::Constant_valueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_main(DapParser::Assign_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_stmt(DapParser::Assign_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBy_main(DapParser::By_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBy_stmt(DapParser::By_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall_main(DapParser::Call_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall_stmt(DapParser::Call_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitData_main(DapParser::Data_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitData_stmt(DapParser::Data_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDataset_name_opt(DapParser::Dataset_name_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDatastmt_cmd(DapParser::Datastmt_cmdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_dsname_opt(DapParser::View_dsname_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitView_name(DapParser::View_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDataset_name(DapParser::Dataset_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgram_name(DapParser::Program_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPasswd_opt(DapParser::Passwd_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSource_opt(DapParser::Source_optContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDatalines_main(DapParser::Datalines_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDatalines_stmt(DapParser::Datalines_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDatalines4_stmt(DapParser::Datalines4_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDrop_main(DapParser::Drop_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDrop_stmt(DapParser::Drop_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInfile_main(DapParser::Infile_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInfile_stmt(DapParser::Infile_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFile_specification(DapParser::File_specificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDevice_type(DapParser::Device_typeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInfile_options(DapParser::Infile_optionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput_main(DapParser::Input_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput_stmt(DapParser::Input_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPut_stmt(DapParser::Put_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput_specification(DapParser::Input_specificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPut_specification(DapParser::Put_specificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPointer_control(DapParser::Pointer_controlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInformat_list(DapParser::Informat_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput_variable_format(DapParser::Input_variable_formatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInput_variable(DapParser::Input_variableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPut_variable_format(DapParser::Put_variable_formatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPut_variable(DapParser::Put_variableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitColumn_point_control(DapParser::Column_point_controlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLine_point_control(DapParser::Line_point_controlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormat_modifier(DapParser::Format_modifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitColumn_specifications(DapParser::Column_specificationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeans_main(DapParser::Means_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMeans_proc(DapParser::Means_procContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRun_main(DapParser::Run_mainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRun_stmt(DapParser::Run_stmtContext *ctx) override {
    return visitChildren(ctx);
  }


};

