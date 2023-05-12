
// Generated from Dap.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "DapParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DapParser.
 */
class  DapListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterParse(DapParser::ParseContext *ctx) = 0;
  virtual void exitParse(DapParser::ParseContext *ctx) = 0;

  virtual void enterSas_stmt_list(DapParser::Sas_stmt_listContext *ctx) = 0;
  virtual void exitSas_stmt_list(DapParser::Sas_stmt_listContext *ctx) = 0;

  virtual void enterIf_stmt(DapParser::If_stmtContext *ctx) = 0;
  virtual void exitIf_stmt(DapParser::If_stmtContext *ctx) = 0;

  virtual void enterIf_then_else_stmt(DapParser::If_then_else_stmtContext *ctx) = 0;
  virtual void exitIf_then_else_stmt(DapParser::If_then_else_stmtContext *ctx) = 0;

  virtual void enterDelete_stmt(DapParser::Delete_stmtContext *ctx) = 0;
  virtual void exitDelete_stmt(DapParser::Delete_stmtContext *ctx) = 0;

  virtual void enterExpression(DapParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(DapParser::ExpressionContext *ctx) = 0;

  virtual void enterExpressionList(DapParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(DapParser::ExpressionListContext *ctx) = 0;

  virtual void enterOf_var_list(DapParser::Of_var_listContext *ctx) = 0;
  virtual void exitOf_var_list(DapParser::Of_var_listContext *ctx) = 0;

  virtual void enterIdentifiers_list(DapParser::Identifiers_listContext *ctx) = 0;
  virtual void exitIdentifiers_list(DapParser::Identifiers_listContext *ctx) = 0;

  virtual void enterIn_var_list(DapParser::In_var_listContext *ctx) = 0;
  virtual void exitIn_var_list(DapParser::In_var_listContext *ctx) = 0;

  virtual void enterColonInts(DapParser::ColonIntsContext *ctx) = 0;
  virtual void exitColonInts(DapParser::ColonIntsContext *ctx) = 0;

  virtual void enterLiteral(DapParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(DapParser::LiteralContext *ctx) = 0;

  virtual void enterVariables(DapParser::VariablesContext *ctx) = 0;
  virtual void exitVariables(DapParser::VariablesContext *ctx) = 0;

  virtual void enterAbort_main(DapParser::Abort_mainContext *ctx) = 0;
  virtual void exitAbort_main(DapParser::Abort_mainContext *ctx) = 0;

  virtual void enterAbort_stmt(DapParser::Abort_stmtContext *ctx) = 0;
  virtual void exitAbort_stmt(DapParser::Abort_stmtContext *ctx) = 0;

  virtual void enterFile_spec(DapParser::File_specContext *ctx) = 0;
  virtual void exitFile_spec(DapParser::File_specContext *ctx) = 0;

  virtual void enterProc_main(DapParser::Proc_mainContext *ctx) = 0;
  virtual void exitProc_main(DapParser::Proc_mainContext *ctx) = 0;

  virtual void enterProc_stmt(DapParser::Proc_stmtContext *ctx) = 0;
  virtual void exitProc_stmt(DapParser::Proc_stmtContext *ctx) = 0;

  virtual void enterProc_name(DapParser::Proc_nameContext *ctx) = 0;
  virtual void exitProc_name(DapParser::Proc_nameContext *ctx) = 0;

  virtual void enterArray_main(DapParser::Array_mainContext *ctx) = 0;
  virtual void exitArray_main(DapParser::Array_mainContext *ctx) = 0;

  virtual void enterArray_stmt(DapParser::Array_stmtContext *ctx) = 0;
  virtual void exitArray_stmt(DapParser::Array_stmtContext *ctx) = 0;

  virtual void enterArray_name(DapParser::Array_nameContext *ctx) = 0;
  virtual void exitArray_name(DapParser::Array_nameContext *ctx) = 0;

  virtual void enterArray_subscript(DapParser::Array_subscriptContext *ctx) = 0;
  virtual void exitArray_subscript(DapParser::Array_subscriptContext *ctx) = 0;

  virtual void enterArray_elements(DapParser::Array_elementsContext *ctx) = 0;
  virtual void exitArray_elements(DapParser::Array_elementsContext *ctx) = 0;

  virtual void enterInitial_value_list(DapParser::Initial_value_listContext *ctx) = 0;
  virtual void exitInitial_value_list(DapParser::Initial_value_listContext *ctx) = 0;

  virtual void enterInitial_value_list_item(DapParser::Initial_value_list_itemContext *ctx) = 0;
  virtual void exitInitial_value_list_item(DapParser::Initial_value_list_itemContext *ctx) = 0;

  virtual void enterInitial_value_list_bk(DapParser::Initial_value_list_bkContext *ctx) = 0;
  virtual void exitInitial_value_list_bk(DapParser::Initial_value_list_bkContext *ctx) = 0;

  virtual void enterConstant_iter_value(DapParser::Constant_iter_valueContext *ctx) = 0;
  virtual void exitConstant_iter_value(DapParser::Constant_iter_valueContext *ctx) = 0;

  virtual void enterConstant_value(DapParser::Constant_valueContext *ctx) = 0;
  virtual void exitConstant_value(DapParser::Constant_valueContext *ctx) = 0;

  virtual void enterAssign_main(DapParser::Assign_mainContext *ctx) = 0;
  virtual void exitAssign_main(DapParser::Assign_mainContext *ctx) = 0;

  virtual void enterAssign_stmt(DapParser::Assign_stmtContext *ctx) = 0;
  virtual void exitAssign_stmt(DapParser::Assign_stmtContext *ctx) = 0;

  virtual void enterBy_main(DapParser::By_mainContext *ctx) = 0;
  virtual void exitBy_main(DapParser::By_mainContext *ctx) = 0;

  virtual void enterBy_stmt(DapParser::By_stmtContext *ctx) = 0;
  virtual void exitBy_stmt(DapParser::By_stmtContext *ctx) = 0;

  virtual void enterCall_main(DapParser::Call_mainContext *ctx) = 0;
  virtual void exitCall_main(DapParser::Call_mainContext *ctx) = 0;

  virtual void enterCall_stmt(DapParser::Call_stmtContext *ctx) = 0;
  virtual void exitCall_stmt(DapParser::Call_stmtContext *ctx) = 0;

  virtual void enterData_main(DapParser::Data_mainContext *ctx) = 0;
  virtual void exitData_main(DapParser::Data_mainContext *ctx) = 0;

  virtual void enterData_stmt(DapParser::Data_stmtContext *ctx) = 0;
  virtual void exitData_stmt(DapParser::Data_stmtContext *ctx) = 0;

  virtual void enterDataset_name_opt(DapParser::Dataset_name_optContext *ctx) = 0;
  virtual void exitDataset_name_opt(DapParser::Dataset_name_optContext *ctx) = 0;

  virtual void enterDatastmt_cmd(DapParser::Datastmt_cmdContext *ctx) = 0;
  virtual void exitDatastmt_cmd(DapParser::Datastmt_cmdContext *ctx) = 0;

  virtual void enterView_dsname_opt(DapParser::View_dsname_optContext *ctx) = 0;
  virtual void exitView_dsname_opt(DapParser::View_dsname_optContext *ctx) = 0;

  virtual void enterView_name(DapParser::View_nameContext *ctx) = 0;
  virtual void exitView_name(DapParser::View_nameContext *ctx) = 0;

  virtual void enterDataset_name(DapParser::Dataset_nameContext *ctx) = 0;
  virtual void exitDataset_name(DapParser::Dataset_nameContext *ctx) = 0;

  virtual void enterProgram_name(DapParser::Program_nameContext *ctx) = 0;
  virtual void exitProgram_name(DapParser::Program_nameContext *ctx) = 0;

  virtual void enterPasswd_opt(DapParser::Passwd_optContext *ctx) = 0;
  virtual void exitPasswd_opt(DapParser::Passwd_optContext *ctx) = 0;

  virtual void enterSource_opt(DapParser::Source_optContext *ctx) = 0;
  virtual void exitSource_opt(DapParser::Source_optContext *ctx) = 0;

  virtual void enterDatalines_main(DapParser::Datalines_mainContext *ctx) = 0;
  virtual void exitDatalines_main(DapParser::Datalines_mainContext *ctx) = 0;

  virtual void enterDatalines_stmt(DapParser::Datalines_stmtContext *ctx) = 0;
  virtual void exitDatalines_stmt(DapParser::Datalines_stmtContext *ctx) = 0;

  virtual void enterDatalines4_stmt(DapParser::Datalines4_stmtContext *ctx) = 0;
  virtual void exitDatalines4_stmt(DapParser::Datalines4_stmtContext *ctx) = 0;

  virtual void enterDrop_main(DapParser::Drop_mainContext *ctx) = 0;
  virtual void exitDrop_main(DapParser::Drop_mainContext *ctx) = 0;

  virtual void enterDrop_stmt(DapParser::Drop_stmtContext *ctx) = 0;
  virtual void exitDrop_stmt(DapParser::Drop_stmtContext *ctx) = 0;

  virtual void enterInfile_main(DapParser::Infile_mainContext *ctx) = 0;
  virtual void exitInfile_main(DapParser::Infile_mainContext *ctx) = 0;

  virtual void enterInfile_stmt(DapParser::Infile_stmtContext *ctx) = 0;
  virtual void exitInfile_stmt(DapParser::Infile_stmtContext *ctx) = 0;

  virtual void enterFile_specification(DapParser::File_specificationContext *ctx) = 0;
  virtual void exitFile_specification(DapParser::File_specificationContext *ctx) = 0;

  virtual void enterDevice_type(DapParser::Device_typeContext *ctx) = 0;
  virtual void exitDevice_type(DapParser::Device_typeContext *ctx) = 0;

  virtual void enterInfile_options(DapParser::Infile_optionsContext *ctx) = 0;
  virtual void exitInfile_options(DapParser::Infile_optionsContext *ctx) = 0;

  virtual void enterInput_main(DapParser::Input_mainContext *ctx) = 0;
  virtual void exitInput_main(DapParser::Input_mainContext *ctx) = 0;

  virtual void enterInput_stmt(DapParser::Input_stmtContext *ctx) = 0;
  virtual void exitInput_stmt(DapParser::Input_stmtContext *ctx) = 0;

  virtual void enterPut_stmt(DapParser::Put_stmtContext *ctx) = 0;
  virtual void exitPut_stmt(DapParser::Put_stmtContext *ctx) = 0;

  virtual void enterInput_specification(DapParser::Input_specificationContext *ctx) = 0;
  virtual void exitInput_specification(DapParser::Input_specificationContext *ctx) = 0;

  virtual void enterPut_specification(DapParser::Put_specificationContext *ctx) = 0;
  virtual void exitPut_specification(DapParser::Put_specificationContext *ctx) = 0;

  virtual void enterPointer_control(DapParser::Pointer_controlContext *ctx) = 0;
  virtual void exitPointer_control(DapParser::Pointer_controlContext *ctx) = 0;

  virtual void enterInformat_list(DapParser::Informat_listContext *ctx) = 0;
  virtual void exitInformat_list(DapParser::Informat_listContext *ctx) = 0;

  virtual void enterInput_variable_format(DapParser::Input_variable_formatContext *ctx) = 0;
  virtual void exitInput_variable_format(DapParser::Input_variable_formatContext *ctx) = 0;

  virtual void enterInput_variable(DapParser::Input_variableContext *ctx) = 0;
  virtual void exitInput_variable(DapParser::Input_variableContext *ctx) = 0;

  virtual void enterPut_variable_format(DapParser::Put_variable_formatContext *ctx) = 0;
  virtual void exitPut_variable_format(DapParser::Put_variable_formatContext *ctx) = 0;

  virtual void enterPut_variable(DapParser::Put_variableContext *ctx) = 0;
  virtual void exitPut_variable(DapParser::Put_variableContext *ctx) = 0;

  virtual void enterColumn_point_control(DapParser::Column_point_controlContext *ctx) = 0;
  virtual void exitColumn_point_control(DapParser::Column_point_controlContext *ctx) = 0;

  virtual void enterLine_point_control(DapParser::Line_point_controlContext *ctx) = 0;
  virtual void exitLine_point_control(DapParser::Line_point_controlContext *ctx) = 0;

  virtual void enterFormat_modifier(DapParser::Format_modifierContext *ctx) = 0;
  virtual void exitFormat_modifier(DapParser::Format_modifierContext *ctx) = 0;

  virtual void enterColumn_specifications(DapParser::Column_specificationsContext *ctx) = 0;
  virtual void exitColumn_specifications(DapParser::Column_specificationsContext *ctx) = 0;

  virtual void enterMeans_main(DapParser::Means_mainContext *ctx) = 0;
  virtual void exitMeans_main(DapParser::Means_mainContext *ctx) = 0;

  virtual void enterMeans_proc(DapParser::Means_procContext *ctx) = 0;
  virtual void exitMeans_proc(DapParser::Means_procContext *ctx) = 0;

  virtual void enterRun_main(DapParser::Run_mainContext *ctx) = 0;
  virtual void exitRun_main(DapParser::Run_mainContext *ctx) = 0;

  virtual void enterRun_stmt(DapParser::Run_stmtContext *ctx) = 0;
  virtual void exitRun_stmt(DapParser::Run_stmtContext *ctx) = 0;


};

