<?xml version="1.0" encoding="windows-1250" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:msxsl="urn:schemas-microsoft-com:xslt" xmlns:dedek="http://reportasistent.com/dedek_namespace" version="1.0">
   
   
   <msxsl:script language="JScript" implements-prefix="dedek">
   
   
	function normalize_value(co, cim)
	{
		var delitel = cim;
		if (delitel == 0)
			delitel = 1;
		return Math.round(100*(co/delitel));
	}

    
   </msxsl:script>

   <!-- Promenne - nastaveni vizualizaci-->
   <xsl:variable name="FirstSetShow">true</xsl:variable>
   <xsl:variable name="SecondSetShow">true</xsl:variable>
   <xsl:variable name="GraphType">xl3DColumn</xsl:variable>
   <xsl:variable name="ValuesType">rel_max</xsl:variable>
   <xsl:variable name="GraphTitle">4ft Graph</xsl:variable>
   <xsl:variable name="LegendShow">false</xsl:variable>
   <xsl:variable name="GraphWidth">75e-2</xsl:variable>
   <xsl:variable name="GraphHeight">75e-2</xsl:variable>
   
   
   
   
   
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />
   <!-- klic - hypotezy (Kody: kvuli pocitani sum sloupcu)-->
<xsl:key name="key_hyp_sdkl" match="hyp_sdkl" use="@id" />

   
   
   
<xsl:template match="hyp_sdkl">

  <xsl:if test="$FirstSetShow='true' or $SecondSetShow='true'">
  
      <xsl:variable name="id_base" select="@id" />
      <xsl:variable name="sum_of_values_set1" select="@sum1" />
      <xsl:variable name="max_value_set1" select="@max1" />
      <xsl:variable name="sum_of_values_set2" select="@sum2" />
      <xsl:variable name="max_value_set2" select="@max2" />

      <paragraph>
      
         <graph title="{$GraphTitle}" showlegend="{$LegendShow}" charttype="{$GraphType}" height="{$GraphHeight}" width="{$GraphWidth}" id="{@id}_sdgraph">
            <xsl:variable name="row_attr_id" select="@row_attributes" />

            <xsl:for-each select="key('key_ti_attribute',@column_attributes)">
               <xsl:call-template name="column_categories" /><!-- vypsani kategorii-->
            </xsl:for-each>

            <xsl:for-each select="tab[position()=1]/r">
               <xsl:variable name="row_number" select="position()" />

               <xsl:variable name="row_values_sum_set1" select="sum(c/@val)" /><!-- sum of values in this row -->
               <xsl:variable name="row_values_sum_set2" select="sum(key('key_hyp_sdkl',$id_base)/tab[position()=2]/r[position()=$row_number]/c/@val)" /><!-- sum of values in this row -->
               <xsl:element name="chart">
                  <xsl:attribute name="title">
                     <xsl:value-of select="key('key_ti_attribute',$row_attr_id)/ti_category[position()=$row_number]/@value" />
                  </xsl:attribute>

                  <xsl:attribute name="id"><xsl:value-of select="$id_base" /><xsl:text>_chart</xsl:text><xsl:value-of select="position()" /></xsl:attribute>



				  <xsl:if test="$FirstSetShow='true'">
                  	<xsl:for-each select="c">
                   	  <xsl:variable name="col_number_set1" select="position()" />
	
    	                 <xsl:variable name="norm_factor_set1"><!-- normalizacni faktor-->
       	                 <xsl:choose>
       	                    <xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="$sum_of_values_set1" /></xsl:when>
       	                    <xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="$max_value_set1" /></xsl:when>
       	                    <xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="$row_values_sum_set1" /></xsl:when>
       	                    <xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="sum(key('key_hyp_sdkl',$id_base)/tab[position()=1]/r/c[position()=$col_number_set1]/@val)" /></xsl:when>
       	                    <xsl:otherwise>100</xsl:otherwise>
       	                 </xsl:choose>
       	              	</xsl:variable>			

                     	<xsl:element name="value">
      	                  <xsl:attribute name="id"><xsl:value-of select="$id_base" /><xsl:text>_val</xsl:text><xsl:value-of select="position()" /></xsl:attribute>

	                        <xsl:attribute name="value">
    	                       <xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor_set1))" />
       	                    <xsl:if test="$ValuesType!='abs'">%</xsl:if>
       	                 </xsl:attribute>
       	              </xsl:element>   
       	           </xsl:for-each>
       	           <xsl:if test="$SecondSetShow='true'">
       	           		<value id="{$id_base}mezera{$row_number}" value=""/>
       	           </xsl:if>
                  </xsl:if> <!-- FirstSetShow-->
                  
                  
                  
                  <xsl:if test="$SecondSetShow='true'">
                  	<xsl:for-each select="key('key_hyp_sdkl',$id_base)/tab[position()=2]/r[position()=$row_number]/c">
                   	  <xsl:variable name="col_number_set2" select="position()" />
	
    	                 <xsl:variable name="norm_factor_set2"><!-- normalizacni faktor-->
       	                 <xsl:choose>
       	                    <xsl:when test="$ValuesType='rel_sum'"><xsl:value-of select="$sum_of_values_set2" /></xsl:when>
       	                    <xsl:when test="$ValuesType='rel_max'"><xsl:value-of select="$max_value_set2" /></xsl:when>
       	                    <xsl:when test="$ValuesType='rel_row'"><xsl:value-of select="$row_values_sum_set2" /></xsl:when>
       	                    <xsl:when test="$ValuesType='rel_col'"><xsl:value-of select="sum(key('key_hyp_sdkl',$id_base)/tab[position()=1]/r/c[position()=$col_number_set2]/@val)" /></xsl:when>
       	                    <xsl:otherwise>100</xsl:otherwise>
       	                 </xsl:choose>
       	              	</xsl:variable>			

                     	<xsl:element name="value">
      	                  <xsl:attribute name="id"><xsl:value-of select="$id_base" /><xsl:text>_val</xsl:text><xsl:value-of select="position()" /></xsl:attribute>

	                        <xsl:attribute name="value">
    	                       <xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor_set2))" />
       	                    <xsl:if test="$ValuesType!='abs'">%</xsl:if>
       	                 </xsl:attribute>
       	              </xsl:element>   
       	           </xsl:for-each>
                  </xsl:if> <!-- SecondSetShow-->
                  
                  
                  
               </xsl:element>
            </xsl:for-each>
         </graph>
      </paragraph>
  
  </xsl:if>

</xsl:template>




   <xsl:template name="column_categories">
   
      <!-- vypise kategorie atributu-->
      <categories id="{@id}_col_cats1">
         <xsl:variable name="id_base" select="@id" />
         
		 <xsl:if test="$FirstSetShow='true'">
    	    <xsl:for-each select="ti_category">
        	    <category title="{@value}" id="{$id_base}_col_cat{position()}_set1" />
         	</xsl:for-each>
         	<xsl:if test="$SecondSetShow='true'">
         		<category title="" id="{$id_base}_col_cat_mezera" />
         	</xsl:if>
         </xsl:if>
         
         <xsl:if test="$SecondSetShow='true'">
         	<xsl:for-each select="ti_category">
        	    <category title="{@value}" id="{$id_base}_col_cat{position()}_set2" />
         	</xsl:for-each>
         </xsl:if>
         
      </categories>
      
   </xsl:template>
   
   
</xsl:stylesheet>

