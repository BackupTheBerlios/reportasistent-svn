<?xml version="1.0" encoding="windows-1250" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:msxsl="urn:schemas-microsoft-com:xslt" xmlns:dedek="http://reportasistent.com/dedek_namespace" version="1.0">
   
   
   <msxsl:script language="JScript" implements-prefix="dedek">
   
   
   function normalize_value(co, cim)
   {
    return Math.round(100*(co/cim)); 
   }
    
   </msxsl:script>

   <!-- Promenne - nastaveni vizualizaci-->
   <xsl:variable name="GraphType">xl3DColumn</xsl:variable>
   <xsl:variable name="ValuesType">rel_col</xsl:variable>
   <xsl:variable name="GraphTitle">4ft Graph</xsl:variable>
   <xsl:variable name="LegendShow">false</xsl:variable>
   <xsl:variable name="GraphWidth">75e-2</xsl:variable>
   <xsl:variable name="GraphHeight">75e-2</xsl:variable>
   
   
   
   
   
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />
   <!-- klic - hypotezy (Kody: kvuli pocitani sum sloupcu)-->
<xsl:key name="key_hyp_kl" match="hyp_kl" use="@id" />

   
   
   
  <xsl:template match="hyp_kl">
  
      <xsl:variable name="id_base" select="@id" />
      <xsl:variable name="sum_of_values" select="@sum" />
      <xsl:variable name="max_value" select="@max" />

      <paragraph>
      
         <graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
            <xsl:variable name="row_attr_id" select="@row_attributes" />

            <xsl:for-each select="key('key_ti_attribute',@column_attributes)">
               <xsl:call-template name="column_categories" /><!-- vypsani kategorii-->
            </xsl:for-each>

            <xsl:for-each select="tab[position()=1]/r">
               <xsl:variable name="row_number" select="position()" />

               <xsl:variable name="row_values_sum" select="sum(c/@val)" /><!-- sum of values in this row -->
               <xsl:element name="chart">
                  <xsl:attribute name="title">
                     <xsl:value-of select="key('key_ti_attribute',$row_attr_id)/ti_category[position()=$row_number]/@value" />
                  </xsl:attribute>

                  <xsl:attribute name="id"><xsl:value-of select="$id_base" /><xsl:text>_chart</xsl:text><xsl:value-of select="position()" /></xsl:attribute>

                  <xsl:for-each select="c">
                     <xsl:variable name="col_number" select="position()" />

                     <xsl:variable name="norm_factor"><!-- normalizacni faktor-->
                        <xsl:choose>
                           <xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="$sum_of_values" /></xsl:when>
                           <xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="$max_value" /></xsl:when>
                           <xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="$row_values_sum" /></xsl:when>
                           <xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="sum(key('key_hyp_kl',$id_base)/tab[position()=1]/r/c[position()=$col_number]/@val)" /></xsl:when>
                           <xsl:otherwise>100</xsl:otherwise>
                        </xsl:choose>
                     </xsl:variable>

                     <xsl:element name="value">
                        <xsl:attribute name="id"><xsl:value-of select="$id_base" /><xsl:text>_val</xsl:text><xsl:value-of select="position()" /></xsl:attribute>

                        <xsl:attribute name="value">
                           <xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor))" />

                           <xsl:if test="$ValuesType!='abs'">%</xsl:if>
                        </xsl:attribute>
                     </xsl:element>
                  </xsl:for-each>
               </xsl:element>
            </xsl:for-each>
         </graph>
      </paragraph>
   </xsl:template>




   <xsl:template name="column_categories">
   
      <!-- vypise kategorie atributu-->
      <categories id="{@id}_col_cats1">
         <xsl:variable name="id_base" select="@id" />

         <xsl:for-each select="ti_category">
            <category title="{@value}" id="{$id_base}_col_cat{position()}" />
         </xsl:for-each>
      </categories>
      
   </xsl:template>
   
   
</xsl:stylesheet>

