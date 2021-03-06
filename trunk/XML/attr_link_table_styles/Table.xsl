<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">




  <xsl:template match="attr_link_table">

    <xsl:text disable-output-escaping="yes">
		</xsl:text>
    <output>
      <paragraph>
        <xsl:variable name="rows_count" select="count(link)"/>
        <xsl:if test="$rows_count > 0">
          <table id="tab{@id}" cols="2" rows="{$rows_count}">
            <xsl:apply-templates select="link">
              <xsl:with-param name="target_active_element">
                <xsl:value-of select="@target"/>
              </xsl:with-param>
            </xsl:apply-templates>



            <xsl:text disable-output-escaping="yes">
		
		</xsl:text>
          </table>
        </xsl:if>
      </paragraph>
    </output>
  </xsl:template>






  <xsl:template match="link">
    <xsl:param name="target_active_element" />

    <xsl:text disable-output-escaping="yes">
		
				</xsl:text>
    <tr id="tr_attr_{@attr_name}">

      <xsl:variable name="attr_name" select="@attr_name"/>


      <xsl:text disable-output-escaping="yes">
					</xsl:text>

      <td>
        <text id="txt1">
          <xsl:value-of select="@caption"/>
        </text>
      </td>
      <td>
        <text id="txt2">
          <xsl:value-of select="id($target_active_element)//attribute[@name = $attr_name]/@value"/>
        </text>
      </td>



      <xsl:text disable-output-escaping="yes">
				</xsl:text>


    </tr>
  </xsl:template>



</xsl:stylesheet>
